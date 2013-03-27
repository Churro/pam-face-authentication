#ifndef _INCL_GUARD_WEBCAM
#define _INCL_GUARD_WEBCAM

#include "cv.h"
#include "highgui.h"
#include "opencv2/highgui/highgui.hpp"

/**
* OpenCV Webcam class. This class provides the opencv image query functions.
*/
class opencvWebcam: public cv::VideoCapture
{
  private:
    int cameraId;
    cv::Mat image;
    IplImage iplImage;
    
    /**
    * Copy constructor
    * @param opencvWebcam, original value to copy
    */
    opencvWebcam(opencvWebcam&);

    /**
    * Assignment operator
    * @param opencvWebcam, original value to assign
    */
    opencvWebcam& operator =(const opencvWebcam&);    

  public:
    /**
    * The Constructor
    * Obtain the camera to use and open it.
    */
    opencvWebcam();
    
    /**
    * The destructor
    */
    virtual ~opencvWebcam();
        
    /**
    * Query image from webcam
    * @result Image from webcam
    */
    IplImage* queryFrame();

    /**
    * Initialize webcam for querying an image
    * @result returns true on success, false on failure
    */
    bool startCamera();
    
    /**
    * Uninitialize webcam structures
    */
    void stopCamera();
};

#endif // _INCL_GUARD_WEBCAM

