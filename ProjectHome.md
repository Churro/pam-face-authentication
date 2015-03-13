## What is this about? ##
PAM Face Authentication is a pluggable authentication module designed for facial authentication. You can use this module for any service that requires authentication, internally handled by the PAM library.

**It's fast, funny and pretty cool!**

Go Ahead. Explore. Have fun. Contribute!

| <a href='http://www.youtube.com/watch?feature=player_embedded&v=PhReQgyprLg' target='_blank'><img src='http://img.youtube.com/vi/PhReQgyprLg/0.jpg' width='425' height=344 /></a> |
|:----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|

## Current project status ##

A long time no update, I know. Nevertheless the project is just sleeping, definitely not given up! Helping hands are always welcome!

  * Large parts should be rewritten using the C++ bindings of OpenCV
  * The face authentication should be abortable by pressing ESC upon login
  * Enabling/disabling should be possible using one-click buttons
  * Recognition might be improvable under bad light conditions
  * The pre-processing of images before recognition should be improved in order to attain higher accuracy.
  * The Qt-GUI can be heavily improved. Currently it has not a really professional look ;)
  * Implement tracking and registration with minimal user supervision
  * Create a dataset to evaluate the performance of authentication methods
  * And a lot of other things to do...

## Installation ##

Currently we have to guides for installation on K(Ubuntu) or from source.
If you are willing to contribute information, please do not hesitate to write us!

[Installation on K(Ubuntu)](https://code.google.com/p/pam-face-authentication/wiki/WikiInstallationGuide)

[Installation from source](https://code.google.com/p/pam-face-authentication/wiki/WikiInstallationFromSource)

### History ###

PFA proposal was selected as one of the projects funded during the Google Summer Code 2008 Program under openSUSE.
` Proposed and Developed - LBP Based Authentication, GTK based Interface `

The project was then extended during the GSOC 2009 under Pardus to make it work with KDE Display Manager.
` Improved Tracking and Authentication algorithm, KDM Plugin, Fixed Issues with GDM & KDM `

### Misc ###

Give us reviews at https://www.ohloh.net/p/pam-face-authentication/reviews/new

We need your help in translating the GUI for version 0.4:
[Download POT File 1](http://pam-face-authentication.googlecode.com/svn/trunk/translation/0.4/pam_face_authentication.pot)
[Download POT File 2](http://pam-face-authentication.googlecode.com/svn/trunk/translation/0.4/qt_facetrainer.pot)

You can also help using an online translator at:
@http://translate.pardus.org.tr/transifex/projects/p/pam-face-authentication/
All of it will be soon added to the projects. Thank you all!

&lt;wiki:gadget url="http://www.ohloh.net/p/59515/widgets/project\_basic\_stats.xml" height="240" border="1"/&gt;

## Packages ##

![http://a1.twimg.com/profile_images/551019596/opensuse_icon_normal.png](http://a1.twimg.com/profile_images/551019596/opensuse_icon_normal.png) [openSUSE (Alessandro Faria)](http://software.opensuse.org/search?baseproject=ALL&p=1&q=pam-face-authentication)

![http://do.davebsd.com/images/download-fedora.png](http://do.davebsd.com/images/download-fedora.png) [Fedora (Steven)](http://forums.fedoraforum.org/showthread.php?p=1355399)

![http://eina.sourceforge.net/img/download-arch.png](http://eina.sourceforge.net/img/download-arch.png) [Arch (x-demon)](http://aur.archlinux.org/packages.php?ID=31088)

[Gentoo (Eitan Mosenkis)](http://bugs.gentoo.org/261902)

# People #

The project is being developed by:

  * **Rohan Anil**, BITS Pilani Goa Campus, India

Rohan Anil, Alex Lau Chun Yin, Onur Küçük, "PAM Face Authentication: An opensource  security module for linux systems", _The Tenth IASTED International Conference on Artificial Intelligence and Applications_, 2010.

  * **Johannes Feichtner**, TU Graz
| [![](http://portal.tugraz.at/portal/page/portal/Files/BDR/CD/images/Logo_TU_Graz.png)](http://www.tugraz.at) |
|:-------------------------------------------------------------------------------------------------------------|