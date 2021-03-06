# Robot-QR-code
Development of Human-tracking Robot using the QR Code recognition in Linux environment. As a result, Robot detects the QR code and follow it. (ROS-based processes)

A human-tracking Robot using the QR code detection for mobile robot localization and navigation is proposed. With a camera and a quick recognition algorithm, the vision system used in the experiment provides a high-accurate and high-speed recognition method for detecting a leader marked with a QR code by a mobile Robot.
The algorithm detects the location of the leader with the probable recognition of matrix codes in an image. Moreover, a Robot-control part is proposed to keep a determined distance from the leader being tracked.

# Powerbot
A mobile robot that was used in this package. 

# QR code
Print the QR code that will be mounted on your leader (it can be an object or human or another robot)
This is an example of a valid QR-code pattern that can be downloaded from [ROS Wiki](http://wiki.ros.org/visp_auto_tracker) or scanning the below QR code

![frame](https://user-images.githubusercontent.com/52676399/96356460-a3dfd100-10a3-11eb-8b1e-1b993a205f68.png)

# Setup

  - Charge robot
  - Turn on NUC or the computer which is conected to the robot
  - Connect laptop to wi-fi
  - Make sure you connect the usb camera to the NUC or the computer
  
  ### Installation

  Install the dependencies for visp_auto_tracker if it isn't installed.
```
  $ cd ~/catkin_ws/src

  $ git clone https://github.com/lagadic/vision_visp.git

  $ cd ..

  $ catkin_make --pkg visp_auto_tracker 
```
  Or
```
  $ catkin build --pkg visp_auto_tracker

  $ source devel/setup.bash
```
# Terminal 1: PS3 Controller

- Connect to NUC/computer with GUI: "ssh -X {user}@{host}". (Password needed)
  - "sudo bash"
  - "rosrun ps3joy ps3joy.py --continuous-output"
     - Press middle button on Joy Stick and see "Connection Activated" 
 

# Terminal 2: Robot Navigation (To control the Robot, we can do as follows)
- Connect to NUC with GUI: "ssh -X {user}@{host}". (Password needed)
   - roslaunch powerbot_nav powerbot_nav.launch
   
   ![final-joystick](https://user-images.githubusercontent.com/52676399/96355606-45f9bc00-1098-11eb-92c0-623207f442c6.gif)
   
# Terminal 3: QR code detection

- Connect to NUC or the computer with GUI: "ssh -X {user}@{host}". (Password needed)
   - "roslaunch visp_auto_tracker tracklive_usb.launch"
- As a result, you can detect the QR code
   ![QR-detection](https://user-images.githubusercontent.com/52676399/96354978-96b9e680-1091-11eb-954f-f3aae5fa1bb1.png)

# Terminal 4: QR code detection topic
- Connect to NUC or the computer with GUI: "ssh -X {user}@{host}". (Password needed)
  - "rostopic echo /visp_auto/object_position" 
- As a result, you can detect position of the QR code
   ![QR-position-detection](https://user-images.githubusercontent.com/52676399/96355009-0d56e400-1092-11eb-84ea-ad05e349b885.png)
   
# Terminal 5: Following QR code
- Connect to NUC or the computer with GUI: "ssh -X {user}@{host}". (Password ineeded)
  - "roscd qr_test" 
  - "roscd src" 
  - "rosrun qr_test qr_test_node qr_following"

# Terminal 6: connect to ros master
- Connect to NUC or the computer with GUI: "ssh -X {user}@{host}". (Password needed)
  - "roscore"













