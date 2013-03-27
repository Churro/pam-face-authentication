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
#include "opencv2/highgui/highgui.hpp"
#include "pam_face_defines.h"

//------------------------------------------------------------------------------
opencvWebcam::opencvWebcam(): cameraId(0)
{
   cv::FileStorage fileStorage(PKGDATADIR "/config.xml", cv::FileStorage::READ);
   if (fileStorage.isOpened() ) {
      cameraId = (int)fileStorage["CAMERA_INDEX"];
   }

   VideoCapture(cameraId);
}

//------------------------------------------------------------------------------
opencvWebcam::~opencvWebcam()
{
}

//------------------------------------------------------------------------------
bool opencvWebcam::startCamera()
{
   if ( !isOpened() ) open(cameraId);
   return (isOpened());
}

//------------------------------------------------------------------------------
void opencvWebcam::stopCamera()
{
   release();
}

//------------------------------------------------------------------------------
IplImage * opencvWebcam::queryFrame()
{
   read(image);
   iplImage = image;
   return &iplImage;
}

