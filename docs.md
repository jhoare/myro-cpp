---
layout: page
title: Docs
permalink: /docs/
---
{:toc}

## API Documentation ##
Is available here: <http://jhoare.github.io/myro-cpp/doc/2.3.0>

## Using VMWare (Windows) ##
If you don't want to install Ubuntu on your computer, I've created a VMWare Image that has Ubuntu Linux 10.04 installed, with the Myro-Cpp library installed and configured.

To do this you'll have to Download VMWare Player (free). <http://www.vmware.com/products/player/>

Then, you can download the image from here: <ftp://ftp.eecs.utk.edu/pub/myro/Myro-Ubuntu.zip> (1.2Gb)

Then extract the .zip file, and open it with VMWare Player. The username is "student" and the password is "myro"

When you first log in, make sure to run a full upgrade by opening a terminal and typing:

~~~
sudo aptitude update
sudo aptitude safe-upgrade
sudo aptitude install myro-cpp-dev
~~~

When you want to connect to your robot, make sure you've given access of the bluetooth to the virtual machine. (Click the bluetooth icon in the bottom right of the window and click connect.)


## Installation on Ubuntu Linux 10.04/10.10 ##
You must set up your system to get at the Launchpad PPA, so you can install the Myro-cpp library:
```
sudo add-apt-repository ppa:myro-cpp-dev/myro-cpp
sudo aptitude update
sudo aptitude install myro-cpp-dev
```

To set up bluetooth, refer to the bluetooth setup instructions here: <http://wiki.roboteducation.org/Linux_Setup>

Afterwards, you should be able to run ```myro_video_stream color``` in your terminal to test that everything is woring.

## Installation on OSX 10.5 and newer (Leopard and Snow Leopard) ##
First, you need to make sure you have the developer tools installed. If you don't have it installed, you can install it off of the Snow Leopard disk, or download it from apple here: <http://developer.apple.com/technologies/tools/>

Next, you can go to the launchpad site: <http://launchpad.net/myro-c++> And download and run the Mac OSX Installer.

After you have this installed, you will need to pair your robot with your computer. To do this, do the following steps:

1. Attach the IPRE Fluke to the scribbler
2.  Turn on the scribbler
3.  Click on the bluetooth icon in the upper right of your toolbar, select "Set up Bluetooth Device"
4.  Follow the wizard, select "Any device" as the device type
5.  Select the IPRE-XXXXXX where XXXXXX is your Fluke's serial number
6.  Enter the Passkey/PIN code (1234)
7.  From the bluetooth menu in the toolbar select "Open Bluetooth Preference"
8.  Highlight the IPRE bluetooth connection name
9.  Select Edit Serial Ports (little gear picture)
    1. Add a serial port to the Fluke via the "+" button if you don't have one already
    2. If you already have a serial port listed, change the port name to "scribbler" all lowercase
    3. Click Apply
10. Select Edit Serial Ports again
    1. Select the "Require pairing for security" button
    2. Click Apply

When you run any programs, enter ```/dev/tty.scribbler``` to connect to your scribbler robot.

You should now have everything set up to be able to compile programs with myro-cpp!


## Compiling Myro-Cpp in OSX ##
If you wish to compile the source yourself, then use this guide. 
If you don't have any reason to do this, it is much faster to use the installer (see above)

First, you need to make sure you have the developer tools installed.
If you don't have it installed, you can install it off of the Snow Leopard disk, or download it from apple here: <http://developer.apple.com/technologies/tools/>

Now that you have this installed, you'll need to install either [fink](http://www.finkproject.org) or Mac Ports (I use fink so for this I'll assume you've installed it as well.)

Now, you'll need to install a few packages:

```
 fink install boost1.35.nopython boost1.35.nopython-shlibs cmake pkgconfig
```

This will take a really long time (hours). 
When it's setting up stuff it will every so often ask you questions, you're safe to always just answer the default or recommended answer.

Make sure that you've set up the approate CFLAGS and friends variables so you can use the fink software to compile things: See Question 8.3 at <http://www.finkproject.org/faq/usage-general.php>

Then, get the source from Download

~~~
tar zxf myro-cpp-x.x.x.tar.gz 
cd myro-cpp-x.x.x
mkdir build ; cd build
cmake .. 
make 
sudo make install 
~~~

Set up your bluetooth as in the question before.
