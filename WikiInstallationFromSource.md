# Installation #

First you have to make sure that all dependencies are installed for PFA. Assuming you are using Ubuntu you would issue this command in a terminal. For other distributions the command differs of course. Nevertheless it should be obvious that "Development Tools" (gcc, make, cmake, ...) are needed as well as [OpenCV](http://opencv.willowgarage.com/wiki/Welcome).

```
sudo apt-get install build-essential cmake qt4-qmake libqt4-dev libx11-dev libcv-dev libcvaux-dev libhighgui-dev libpam0g-dev checkinstall 
```

Then the PAM module has to be downloaded, compiled and installed:

```
cd /tmp && wget http://pam-face-authentication.googlecode.com/files/pam-face-authentication-0.3.tar.gz
tar zxf pam-face-authentication-0.3.tar.gz && cd pam-face-authentication-*
mkdir build && cd build
cmake -D CMAKE_INSTALL_PREFIX=/usr ..
make
sudo checkinstall --pkgname=pam-authentication-face-auth 
```

# Configuration #

Now it's necessary to learn some face figures to the system. Therefore start the facetrainer app from your start menu and follow the indicated instructions. For being able to login using face authentication, the module must be enabled first. So you have to execute the following in your terminal (**at once**):

```
cat << EOF | sudo tee /usr/share/pam-configs/face_authentication /dev/null
Name: face_authentication profile
Default: yes
Priority: 900
Auth-Type: Primary
Auth:
[success=end default=ignore] pam_face_authentication.so enableX
EOF 
```
By this action, the file _/usr/share/pam-configs/face\_authentication_ is created and contains the plugin information.
With the next command you can **enable** or **disable** the plugin:
```
sudo pam-auth-update --package face_authentication 
```


# Uninstallation #

In order to remove pam-face-authentication from your system, just do the steps in reverse order. First you have to deselect the plugin, then remove the PAM config file.

```
sudo pam-auth-update --package face_authentication
sudo rm /usr/share/pam-configs/face_authentication 
```

As "checkinstall" was used for handling the installation process, you should be able to remove the PFA module by uninstalling with a package manager like dpkg on Ubuntu/Debian:

```
sudo dpkg -r pam-authentication-face-auth 
```