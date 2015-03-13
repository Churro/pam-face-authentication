# Introduction #

The following installation guide might differ slightly for your version of (K)Ubuntu. Apart from that it could occur that new versions of OpenCV bring in some incompatibilities (you are warned ;))

Note For **Ubuntu 12.04**: There were changes in OpenCV which require some adjustments to be made. So for Ubuntu 12.04 please see: http://mundodacana.blogspot.com.br/2012/10/autenticacao-facial-no-ubuntu-12.html

In nearer future, the commands mentioned there will be incorporated here too.

# Installation #

First open a [terminal](https://help.ubuntu.com/community/UsingTheTerminal), then proceed with the following commands:
```
sudo add-apt-repository ppa:antonio.chiurazzi
sudo apt-get update
sudo apt-get install pam-face-authentication
```
Note: The above adds a non-official repository to your list of valid sources. This is not an offical build.

The commands above add the Ubuntu repository for pam-face-authentication to your package source list and then the plugin is actually installed.

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
Note: the above adds pam-face-authentication to your common-auth (/etc/pam.d/common-auth) if used. You may experience problems with this configuration. I suggest you commont out the line that reads simular to the following:
```
#auth	[success=2 default=ignore] pam_face_authentication.so enableX 
```
This is an incomplete fix, but may help if you have issues with su or sudo.

# Uninstallation #

In order to remove pam-face-authentication from your system, just do the steps in reverse order. First you have to deselect the plugin, then remove the PAM config file and lastly the package itself.

```
sudo pam-auth-update --package face_authentication
sudo rm /usr/share/pam-configs/face-authentication
sudo apt-get remove pam-face-authentication 
```