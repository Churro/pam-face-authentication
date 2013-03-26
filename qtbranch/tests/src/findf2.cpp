#include <iostream>
#include <stdio.h>
#include "opencv.hpp"

using namespace std;
using namespace cv;

class faceDetector
{
	public:
		faceDetector( CascadeClassifier &casclass):
			faceDetected(false),
			classifier(casclass),
			scale(1.1),
			neighbors(2)
		{
			minSize = cvSize(40,40);
		}
		~faceDetector(){};
		bool checkFaceDetected() {
			return faceDetected;
		}
		void runFaceDetector( Mat &img) {
			faceDetected = false;
			vector<Rect> objects;
			classifier.detectMultiScale(img, objects, scale, neighbors, CV_HAAR_DO_CANNY_PRUNING, minSize);
			if ( objects.size() > 0)
				faceDetected = true;
		}
		double getScale() { return scale;};
		void setScale(double newScale) { scale = newScale;};
		double getNeighbors() { return neighbors;};
		void setNeighbors(double newNeighbors) { neighbors = newNeighbors;};
		CvSize getMinSize() { return minSize;};
		void setMinSize(CvSize &newMinSize) { minSize = newMinSize;};
	private:
		int faceDetected;
		double scale;
		int neighbors;
		CvSize minSize;
		CascadeClassifier &classifier;
};

int main( int argc, char **argv)
{
	int done = 0;
	int images = 0,
		faces=0;
	double scale = 0.0;
	VideoCapture capture;
	String input("../../data/Test-input/daylight.avi");
	String haars("/usr/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml");

	if ( argc > 1 ) input = argv[1];
	if ( argc > 2 ) if (argv[2][0] != 'N' ) haars = argv[2];
	if ( argc > 3 ) if (argv[3][0] != 'N' ) scale = strtod(argv[3], NULL);
	capture.open(input);
	CascadeClassifier classifier(haars);

	if (!capture.isOpened() )
	{
		cout << "Can not open " << input << "\n";
		exit(1);
	}
	while (!done) {
		Mat img;
		
		capture >> img;
		if ( !(img.empty()) ) {
			images++;
			faceDetector newDetector(classifier);

			if ( scale != 0.0 ) newDetector.setScale(scale);

			newDetector.runFaceDetector(img);
			if (newDetector.checkFaceDetected() > 0 ) {
				faces++;
			} else {
				cout << "Missed face in frame " << images << "\n";
				char s[100];
				snprintf( s, sizeof(s),
					"Missed_find2_%d.jpg", images);
				imwrite(s, img);
			}
		} else {
			done++;
		}
		if ( (images %10) == 0)
			cout << "Progress Faces "<< faces << " images " <<  images << "\n";
	}
	cout << "Total Faces "<< faces << " images " <<  images << "\n";

	return( faces - images);
	
}
