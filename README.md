# Robot-QR-code-follower
Development of Human-tracking Robot using the QR Code recognition in Linux environment. As a result, Robot detects the QR code and follow it. (ROS-based processes)

# Setup

  - Charge robot
  - Turn on NUC or the computer which is conected to the robot
  - Connect laptop to wi-fi
  - Make sure you connect the usb camera to the NUC or the computer which is connected to the robot

# Terminal 1: PS3 Controller

- Connect to NUC/computer with GUI: "ssh -X {user}@{host}". (Password in magic equation.)
  - "sudo bash"
  - "rosrun ps3joy ps3joy.py --continuous-output"
     - Press middle button on Joy Stick and see "Connection Activated" 
 

# Terminal 2: Robot Nav (To control the Robot, we can do as follows)
- Connect to NUC with GUI: "ssh -X {user}@{host}". (Password in magic equation.)
   - roslaunch powerbot_nav powerbot_nav.launch

# Terminal 3: QR code detection

- Connect to NUC with GUI: "ssh -X {user}@{host}". (Password in magic equation.)
   - "roslaunch visp_auto_tracker tracklive_usb.launch"

# Terminal 4: QR code detection topic
- Connect to NUC with GUI: "ssh -X {user}@{host}". (Password in magic equation.)
  - "rostopic echo /visp_auto/object_position" 

# Terminal 5: Following QR code
- Connect to NUC with GUI: "ssh -X {user}@{host}". (Password in magic equation.)
  - "roscd qr_test" 
  - "roscd src" 
  - "rosrun qr_test qr_test_node qr_following"

# Terminal 6: connect with ros master
- Connect to NUC with GUI: "ssh -X {user}@{host}". (Password in magic equation.)
  - "roscore"



### Installation

Install the dependencies for visp_auto_tracker if it isn't installed.

$ cd ~/catkin_ws/src

$ git clone https://github.com/lagadic/vision_visp.git

$ cd ..

$ catkin_make --pkg visp_auto_tracker 

Or

$ catkin build --pkg visp_auto_tracker

$ source devel/setup.bash









