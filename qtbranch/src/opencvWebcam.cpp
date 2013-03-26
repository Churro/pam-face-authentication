/*
    OpenCV Webcam CLASS
    Copyright (C) 2010 Rohan Anil (rohan.anil@gmail.com) -BITS Pilani Goa Campus
    http://www.pam-face-authentication.org

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, version 3 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "opencvWebcam.h"
#include "cv.h"
#include "highgui.h"
#include "pam_face_defines.h"

//------------------------------------------------------------------------------
opencvWebcam::opencvWebcam(): capture_(0)
{
}

//------------------------------------------------------------------------------
opencvWebcam::~opencvWebcam()
{
}

//------------------------------------------------------------------------------
bool opencvWebcam::startCamera()
{
   int i = 0;
   CvFileStorage* fileStorage = cvOpenFileStorage(PKGDATADIR "/config.xml", 0, CV_STORAGE_READ);
   
   if(fileStorage)
   {
     i = cvReadIntByName(fileStorage, 0, "CAMERA_INDEX", 0);
     cvReleaseFileStorage(&fileStorage);
   }

   capture_ = cvCaptureFromCAM(i);
   if(!capture_) capture_ = cvCaptureFromCAM(CV_CAP_ANY);
   if(!capture_) return false;
     else return true;
}

//------------------------------------------------------------------------------
void opencvWebcam::stopCamera()
{
   if(capture_) cvReleaseCapture(&capture_);
}

//------------------------------------------------------------------------------
IplImage* opencvWebcam::queryFrame()
{
    IplImage* originalFrame = cvQueryFrame(capture_);
    if(!originalFrame) return 0;
    
    if(originalFrame->origin != IPL_ORIGIN_TL)
      cvFlip(originalFrame, NULL, 0);
    
    return originalFrame;
}

