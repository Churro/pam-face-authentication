/*
    Utility Functions 2
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

#include <QtGui>
#include <cxcore.h>
#include "cv.h"
#include "highgui.h"
#include "pam_face_defines.h"
#include "qtUtils.h"

//------------------------------------------------------------------------------
QImage* QImageIplImageCvt(IplImage* input)
{
    IplImage *frame = 0;
    if(!input) return 0;

    // TODO: Make constructor/destructor in order to free the alloc'ed QImage
    QImage* image = new QImage(IMAGE_WIDTH, IMAGE_HEIGHT, QImage::Format_RGB32);
    QRgb value;
    uchar* pBits = image->bits();
    int nBytesPerLine = image->bytesPerLine();

    /**
    * Convert the image to the size needed for the display, if required.
    *   else just use the original image.
    * TODO use the size of the QT scene
    */
    if ( (input->height != IMAGE_HEIGHT) || (input->width != IMAGE_WIDTH) ) {
        frame = cvCreateImage( cvSize( IMAGE_WIDTH, IMAGE_HEIGHT),
                IPL_DEPTH_8U, input->nChannels);
        cvResize( input, frame, CV_INTER_LINEAR);
        input = frame;
    }

    for(int n = 0; n < IMAGE_HEIGHT; n++)
    {
        uchar* scanLine = pBits + n * nBytesPerLine;
        for(int m = 0; m < IMAGE_WIDTH; m++)
        {
            CvScalar s = cvGet2D(input, n, m);
            QRgb value = qRgb((uchar)s.val[2], (uchar)s.val[1], (uchar)s.val[0]);

            ((uint *)scanLine)[m] = value;
            //image->setPixel(m, n, value);
        }
    }

    if ( frame != NULL)   // We allocated a new frame so release it
        cvReleaseImage(&frame);
    return image;
}
/* vim: set ts:4 sw:4 ai et */

