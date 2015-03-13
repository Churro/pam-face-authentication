### CALL FOR PARTICIPATION (send mail to anyone of us) ###


===In Progress=== [last minute fixes in progress ](.md)

~~#Fresh GUI (FIXED: facemanager Working on GtkFaceAuthenticate, 25th Feb 2009)~~

~~#Fix Xauthority Bug (FIXED: Updated Svn, 24th Feb 2009)~~
| ![http://pam-face-authentication.googlecode.com/svn/trunk/logo.png](http://pam-face-authentication.googlecode.com/svn/trunk/logo.png) |
|:--------------------------------------------------------------------------------------------------------------------------------------|
~~#Artwork  (TO DO : Anyone Interested)~~

~~#SVM'S For Face Recognition (Work Started)
Fusion of
(( Dctmod-2)   && ( LBP )  ---> SVM ) classifier | Removed PCA , giving 99.4558 / 100 percent accuracy  when i do n-fold cross validation~~

~~#Combine Viola and Jones + LK Inverse Compositional Tracker (Finished with 6 affine parameters, | tracking not as good as i had imagined, 1st March 2009)~~

~~#Added LBP ChiSquare Distance for Imposter Detection March 22 2009~~

~~TODO: FIX Segfault in facedetection module~~ DONE!


### Compile New Code from SVN : Requirements ###
# All code in this package requires the **OpenCV library** (known working
version is **1.0.0** ):
http://sourceforge.net/projects/opencvlibrary/

~~# Some functions require the **Gnu Scientific Library (GSL)** (known working
version is 1.9):~~
~~http://www.gnu.org/software/gsl/~~~~


# **libpam-devel** (>= 0.99.8)
## New ##
**Update April 14th 2009 SVN**
# **gstreamer-0.10**
# **gstreamer-0.10-devel**

Installation Intruction for v.03 from SVN
```
svn checkout http://pam-face-authentication.googlecode.com/svn/trunk/ pam-face-authentication
cd pam-face-authentication
./autogen.sh
./configure
make
su root
make install
```

Hello Everyone!
its been month , not much progress! , i will be starting work from May 23rd
this project has been accepted to be continued by Me(Rohan) under Organization Pardus as a Google Summer of Code 2009  student project, i will be mentored by Onur Küçük

## **Update 29th June 2009** ##
> : Qt Ui is being written and Also Algorithm has been changed to MACE filter(giving good Verification score). A advanced configuration option is being added to manually control the thresholds.

  1. Project Needs A Wiki and Forum , buying the domain soon :)
  1. If you guys have ideas for the project name , mail me :)
  1. Mapping out a Good Way for the project work smoothly with GDM 2.24+ and KDM4
  1. Thank you for the support and patience =)
  1. Realization that the icon i made doesnt look good , if you are good with UI and have enough time :) please do contribute :P

## **Update 7th July 2009** ##
  1. Wrestling with KDM Plugin , Found a way to get GDM to start a gui =)
  1. GtkInterface for the QtBranch will take a day or two
  1. Got the MACE FILTER code reviewed by an Expert =)
  1. Cmake makes it Easy :)
  1. Will release the code very Soon =)


## **Update 20th July 2009** ##
  1. KDM Patch Created
  1. KDM Plugin Created
  1. GDM Work Started

## Update 23rd July 2009 ##
  1. Documentation Started
  1. Mailing list setup
> @ http://lifeasiknow-it.com/mailman/listinfo/pamfaceauthentication-discuss_lifeasiknow-it.com
  1. GDM work In Progress


## Update 8th August 2009 ##
Version 0.3 Released