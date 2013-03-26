#include <iostream>
#include "opencv.hpp"
#include "faceDetector.h"

using namespace std;
using namespace cv;

int main( int argc, char **argv)
{
	int done = 0;
	int images = 0,
		faces=0;
	VideoCapture capture;
	String input("../../data/Test-input/test.avi");

	if ( argc > 1 ) input = argv[1];
	capture.open(input);

	if (!capture.isOpened() )
	{
		capture.open(atoi(argv[1]));
		if (!capture.isOpened() )
		{
			cout << "Can not open " << input << "\n";
			exit(1);
		}
	}
	while (!done) {
		Mat img;
		
		capture >> img;
		if ( !(img.empty()) ) {
			images++;
			faceDetector newDetector;

			IplImage image(img);
			newDetector.runFaceDetector(&image);
			if (newDetector.checkFaceDetected() > 0 ) {
				faces++;
			} else {
				cout << "Miss in frame " << images << "\n";
				char s[100];
				snprintf( s, sizeof(s),
					"Missed_find2_%d.jpg", images);
				imwrite(s, img);
			}
		} else {
			done++;
		}
	}
	printf ("Faces %d, images %d\n", faces, images);

	return( faces - images);
	
}
