/*
    Eye detector class
    Copyright (C) 2010 Rohan Anil (rohan.anil@gmail.com) -BITS Pilani Goa Campus
    http://www.pam-face-authentication.org/

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

#define DEBUG 1
#include <string>
#ifdef DEBUG
#include <iostream>
#endif
#include <cv.h>
#include <highgui.h>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "eyesDetector.h"
#include "pam_face_defines.h"


using std::string;

double CenterofMass(IplImage* src, int flagXY);

const string HAAR_CASCADE_EYE = PKGDATADIR "/haarcascade_eye_tree_eyeglasses.xml";
const string HAAR_CASCADE_EYE_2 = PKGDATADIR "/haarcascade_eye.xml";

//------------------------------------------------------------------------------
eyesDetector::eyesDetector() : bothEyesDetected_(false)
{
    // Load two cascade files
    nested_cascade_.load(HAAR_CASCADE_EYE.c_str());
    nested_cascade_2_.load(HAAR_CASCADE_EYE_2.c_str());
    
    // Setup the storage and clear it
    storage_ = cvCreateMemStorage(0);
    cvClearMemStorage(storage_);
    
    // Initialize eyesInformation Params
    eyesInformation.LE = cvPoint(0, 0);
    eyesInformation.RE = cvPoint(0, 0);
    eyesInformation.Length = 0;
}

//------------------------------------------------------------------------------
eyesDetector::~eyesDetector()
{
    if(storage_) cvReleaseMemStorage(&storage_);
}

//------------------------------------------------------------------------------
void eyesDetector::runEyesDetector(IplImage* input, IplImage* fullImage, CvPoint LT)
{
    bothEyesDetected_ = false;
    
    int scale = 1;
    bool leftT = false, rightT = false;

    // (Re-)initialize eyesInformation params
    eyesInformation.LE = cvPoint(0, 0);
    eyesInformation.RE = cvPoint(0, 0);
    eyesInformation.Length = 0;

    cvClearMemStorage(storage_);
    
    // If no image is given, return
    if(input == 0) return;
    
    IplImage* gray = cvCreateImage(cvSize(input->width, input->height/2), 8, 1);
    IplImage* working = gray;
    IplImage* gray_fullimage = cvCreateImage(cvGetSize(fullImage), 8, 1);

    // Only create scales image if we are scaling (reduces accuracy at low res)
    IplImage* gray_scale = NULL;
    if ( scale != 1) {
        gray_scale = cvCreateImage(cvSize(input->width / scale,
                                      input->height / (2*scale)), 8, 1);
        working = gray_scale;
    }

    cvSetImageROI(input, cvRect(0, (input->height) / 8, input->width,
      (input->height) / 2));
    cvCvtColor(input, gray, CV_BGR2GRAY);
    cvResetImageROI(input);

    cvCvtColor(fullImage, gray_fullimage, CV_BGR2GRAY);
    if( gray_scale) cvResize(gray, gray_scale, CV_INTER_LINEAR);
    
    // Perform histogram equalization (increases contrast and dynamic range)
    cvSmooth(working, working, CV_GAUSSIAN,3,3);
    cvEqualizeHist(working, working);    
    
    std::vector<cv::Rect> nested_objects;
    // First round of Haar detection using nested_cascade_
    nested_cascade_.detectMultiScale( working, nested_objects, 1.1, 2, 0, cvSize(20, 20));
    
    int count = nested_objects.size();
#ifdef DEBUG
    std::cout << "Cascade " << HAAR_CASCADE_EYE << " Found " <<  count << std::endl;
    std::cout << "locations :";
    for(int j = 0; j < nested_objects.size(); j++)
    {
        std::cout << "i:"<< j << " " << nested_objects[j] << std::endl;
    }
#endif
    if(count < 2)
    {
        // Second round of detection using nested_cascade_2_
        nested_cascade_2_.detectMultiScale( working, nested_objects, 1.1, 2, 0, cvSize(20, 20));
          
        count = nested_objects.size();
#ifdef DEBUG
        std::cout << "Cascade " << HAAR_CASCADE_EYE_2 << " Found " <<  count << std::endl;
        std::cout << "locations :";
        for(int j = 0; j < nested_objects.size(); j++)
        {
            std::cout << "i:"<< j << " " << nested_objects[j] << std::endl;
        }
#endif
    }

    if(count > 0)
    {
        for(int j = 0; j < nested_objects.size(); j++)
        {
            cv::Point center;
            cv::Rect nr = nested_objects[j];
            center.x = cvRound((LT.x + (nr.x + nr.width*0.5)*scale));
            center.y = cvRound((LT.y + (input->height)/8 + (nr.y + nr.height*0.5)*scale));

            if((center.x - 4) > 0 && ((center.x - 4) < (gray_fullimage->width-8)) && 
               (center.y - 4) > 0 && ((center.y - 4) < (gray_fullimage->height-8)))
            {
                cvSetImageROI(gray_fullimage, cvRect(center.x - 4, center.y - 4, 8, 8));
                
                IplImage* eyeDetect = cvCreateImage(cvSize(8, 8), 8, 1);
                cvResize(gray_fullimage, eyeDetect, CV_INTER_LINEAR);
                cvResetImageROI(gray_fullimage);

                double xCordinate = (center.x - 4 + CenterofMass(eyeDetect, 0));
                double yCordinate = (center.y - 4 + CenterofMass(eyeDetect, 1));

                cvReleaseImage(&eyeDetect);
                if(center.x < cvRound(LT.x + input->width*0.5))
                {
                    eyesInformation.LE.x = xCordinate;
                    eyesInformation.LE.y = yCordinate;

#ifdef DEBUG
                    cvCircle(fullImage, cvPoint(eyesInformation.LE.x,eyesInformation.LE.y), 
                        4, CV_RGB(0,255,0), 1, 8, 0);
#endif
                    leftT = true;

                }
                else
                {
                    eyesInformation.RE.x = xCordinate;
                    eyesInformation.RE.y = yCordinate;

#ifdef DEBUG
                    cvCircle( fullImage, cvPoint(eyesInformation.RE.x,eyesInformation.RE.y), 
                      4, CV_RGB(0,255,0), 1, 8, 0);
#endif
                    rightT = true;
                }
            }
        }

        if(leftT && rightT)
        {
            eyesInformation.Length = sqrt(pow(eyesInformation.RE.y - eyesInformation.LE.y, 2)
              + pow(eyesInformation.RE.x - eyesInformation.LE.x, 2));
            bothEyesDetected_ = true;
        }
    }

#ifdef DEBUG
    std::cout << "Eyes Len ("<< eyesInformation.Length <<") LE @(" << eyesInformation.LE.x
        << "," << eyesInformation.LE.y << ") RE @(" << eyesInformation.RE.x <<","
        << eyesInformation.RE.y<< ")" << std::endl;
#endif

    cvReleaseImage(&gray_fullimage);
    cvReleaseImage(&gray);
    if ( gray_scale ) cvReleaseImage(&gray_scale);
}

//------------------------------------------------------------------------------
bool eyesDetector::checkEyeDetected()
{
    if(bothEyesDetected_ == true) 
        return true;
    else
        return false;
}

