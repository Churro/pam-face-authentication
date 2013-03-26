#include <iostream>
#include <dirent.h>
#include "opencv.hpp"
#include "eyesDetector.h"
#include "faceDetector.h"

using namespace std;
using namespace cv;

int main( int argc, char **argv)
{
	int images = 0,
	    eyes=0;
	struct dirent* de = NULL;
	VideoCapture capture;
	String directory("./test/");
	String prefix("clipped_");

	if ( argc > 1 ) directory = argv[1];
	if ( argc > 2 ) prefix = argv[2];
	DIR* d=opendir(directory.c_str());
	while ((de = readdir(d)) != NULL)
	{
		if (	(strcmp(de->d_name + strlen(de->d_name)-3, "jpg") == 0)
			&& (strncmp(de->d_name, prefix.c_str(), 8) == 0) )
		{
			String file(directory+"/"+de->d_name);
			capture.open(file);

			if (!capture.isOpened() )
			{
				cout << "Can not open " << file << "\n";
				break;
			}


			Mat img;

			capture >> img;
			if ( !(img.empty()) ) {
				eyesDetector newDetector;
				struct face aface;
				aface.LT = cvPoint(0, 0);
				aface.Width=img.cols;
				aface.Height=img.rows;
				aface.RB = cvPoint(aface.Width, aface.Height);

				images++;
				cout << "Eye check " << de->d_name << " ("
                    << images << ") ";
				IplImage image(img);
				IplImage *dummy = cvCreateImage(cvSize(img.rows, img.cols), 
						8, 3);
				newDetector.runEyesDetector(&image, dummy, aface.LT);
				if(newDetector.checkEyeDetected() != true) {
					char s[100];
					snprintf( s, sizeof(s),
							"noeye_%d.jpg", images);
					cvSaveImage(s, &image);
				} else {
					eyes++;
				}
                cout << "\n";
				cvReleaseImage(&dummy);

			}
			capture.release();
		}
	}
	closedir(d);
	printf ("Eyes %d, images %d\n", eyes, images);

	return( eyes - images);

}
