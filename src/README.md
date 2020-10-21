# Tutorial

```
$ Sudo bash
```
Internet connection on nuc
```
$ username@IP Address: $ firefox
```
RosRun
Launch File is an XML document and a program that launches multiple ROS Nodes.
We can find in the launch file
```
$ Rosrun (name of package) (name of node)//in the launch file exactly 
```
Custome nodes name
```
$ Rosrun list # give us the list name of custom nodes
$ Sudo bash 
```
Reference in [ROS Wiki](http://wiki.ros.org/roslaunch)

```
$ Sudo bash
```
Notes for ROS Nav-STACK Running
Turn on powerbot and nuc and connect to wifi and ssh
```
$ ping nuc
 //check nuc can be ping to the computer!
$ ssh username@IP Address -X 
 //”ssh username@IP Address -X” to connect to nuc computer through our computer
```
1. Connect Joystick
```
$ sudo bash
$ rosrun ps3joy ps3joy.py --continuous-output
```
2. launch
New tab
```
$ ssh username@IP Address -X
$ roslaunch powerbot_nav powerbot_nav.launch 
 //powerbot package & powerbot launch file
```
3. Rviz
New tab
```
$ ssh username@IP Address -X
$ username@IP Address:~$ roscd powerboat_nav/rviz/
```
Note: Wight is the current map in up stair map. Black is the previous in lab map
change branch: 
```
$ username@IP Address: ~/ws/src/powerboat_nav/rviz$ git status 
 //which branch
$ username@IP Address: ~/ws/src/powerboat_nav/rviz$ git checkout -b Maryam 
 //create a new branch (-b)
username@IP Address: ~/catkin_ws/src/powerboat_nav/rviz$ git status 
 //which branch
username@IP Address: ~/catkin_ws/src/powerboat_nav/rviz$ git checkout 2019PADemo-lcs 
 //switch to another branch
username@IP Address: ~/catkin_ws/src/powerboat_nav/rviz$ git status
 //which branch
username@IP Address: ~/catkin_ws/src/powerboat_nav/rviz$ git checkout
 //all branch
username@IP Address: ~/catkin_ws/src/powerboat_nav/rviz$ rosrun rviz rviz -d powerbot_nav.rviz
```
In nuc, edit info in package (like map)
information about ```“yaml”```, configuration parameters, ```cmd_vel``` (is sent by multiplexer, another computer inside the powerboat instead of nuc, run the ROSARIA) which we can change:
<>Note: Joysteak ```(10)>move_base (1):``` means priority with Joysteak.</>
```
$ rosed powerbot_nav powerbot_nav.launch
 //edit and see info (find info in part of map)
$ :q 
 //for exit
```
```
$ roscd powerboat_nav/maps
 //go to folder;
 // wrong: roscd catkin_ws/src/powerboat_nav/launch
ls //shows what is included in the folder: 
   //like the map folder, 
   //icics_x_wing_F0.yaml (caris lab) or x209_20180926.yaml 
$ roslaunch powerbot_nav powerbot_nav.launch map:= x209_20180926.yaml //error
```
```
$ roscd powerboat_nav/launch
 // go to folder
$ username@IP Address: ~/catkin_ws/src/powerboat_nav/launch$ vi powerbot_nav.launch
 //edit the launch. Like map info.
 // Or “vim or gedit powerbot_nav.launch! wrong:empty”
$ username@IP Address: ~/catkin_ws/src/powerboat_nav/launch$ git status
 //check which branch. We can see what we changed
$ username@IP Address: ~/catkin_ws/src/powerboat_nav/launch$ cd .../maps/ //go to map folder
$ username@IP Address: ~/catkin_ws/src/powerboat_nav/map$ ls
 //what else in the folder. X209_20180926.yaml
$ username@IP Address: ~/catkin_ws/src/powerboat_nav/map$ git diff
 //red: the old change; green: the new one
$ roslaunch powerbot_nav powerbot_nav.launch
 //then run the launch to see the new map
```
**Note: There are 2 errors in red color when we run launch. Because we don’t use them. 1. Joystick, 2. Realsense
```
$ username@IP Address:~ rqt_graph
 //give node and topic connection.
```
Topic= connection between nodes. 
Nodes= line program. 
Massages are included in the topic.

 
## example of Turtlebot
1.	Go to simulation_ws/src or catkin_ws/src
2.	“git clone “web””
3.	Simulation >> launch file >> turtle_gazebo package  main.launch
4.	After running the launch file
```
$ Rostopic list 
$ Rostopic info /cmd_vel
 // Rostopic info /topic
$ Rostopic pub /cmd_vel geometry_msgs/twist “tab”
 // Rostopic publish /topic TypeOfMessage “tab”
```
To see the topic, first, we have to roslaunch the package.

Person_follower
See the code (Nodes)
```
$ roscd person_follower/
$ :~/catkin_ws/src/person_follower$ ls
 //person_follower_controller.py
$ :~/catkin_ws/src/person_follower/nodes$ gedit person_follower_controller.py
$ :~/catkin_ws/src/person_follower/nodes$ cd
```
For see in home, we must email Wesly about “person_follower” and “people_follower”

 
Mira Robot Follows the Ball
work with OpenCV
1. detect the ball
1. rostopic list
There are 3 command
```
/mira/pitch_joint_position_controller/command
/mira/roll_joint_position_controller/command
/mira/yaw_joint_position_controller/command
```
2. move the ball
```
Roslaunch package launch.file
roslaunch blob_tracking move_ball_keyboard.lauch
```
![moveBall](https://user-images.githubusercontent.com/52676399/96692248-ab6cd780-133a-11eb-9bed-79054546efe8.png)

3. What mira camera see
Rviz or rosrun
```
rosrun rqt_image_view rqt_image_view
```
camera topic info >> open graphical interface
in simulation >> select image_raw to see the position of ball

![3 1](https://user-images.githubusercontent.com/52676399/96692335-c3445b80-133a-11eb-8fe1-b087c6048cfe.png)

![3 2](https://user-images.githubusercontent.com/52676399/96692444-e40cb100-133a-11eb-8e90-98e7accb8f00.png)

4. object tracking with OpenCV & python, color encoding
```
roslaunch blob_tracking start_colour_gui.launch
```
 
Holobot_ros package
Camera
```
$ /catkin_ws/src/holobot_ros$ ls
 //… src launch
$ /catkin_ws/src/holobot_ros$ cd launch
$ /catkin_ws/src/holobot_ros$ ls launch
 //track_robot.launch usb_cam_eken.launch
$ cat launch/track_robot.launch 
 //see the launch file in section “usb_cam”
Or
$ roscat holobot_ros track_robot.launch
Or
$ roscd holobot_ros
$ /catkin_ws/src/holobot_ros$ git status
 //Maryam
$ /catkin_ws/src/holobot_ros$ gedit launch/track_robot.launch
$ /catkin_ws/src/holobot_ros$ cd
$ roslaunch holobot_ros track_robot.launch
 //Wight error; 
 //ResourceNotFound: ar_track_alvar
 //So, install package ar_track_alvar
 //Ros Path…; error
$ sudo apt-get install ros-kinetic-ar-track-alvar
 // sudo apt-get install ros-indigo-ar-track-alvar 
 //type of ros : indigo or kinetic; like windows
 //orange error: camera calibration not found
 //Next Step:
 //install camera calibration package & use calibration board
```
Hardware (video in launch file-I must change: video1, video 2, video3)
```
$ ls /dev
```
myo running (creating node)
```
$ roscd (name of package)
$ roscd myo_gesture_controller/
$ :~/catkin_ws/src/myo_gesture_controller$ cd script
$ :~/catkin_ws/src/myo_gesture_controller/script$ ls
     //all files included .sh
     //In “Maryam” branch
$ :~/catkin_ws/src/myo_gesture_controller/script$ git checkout Maryam                                                                          /    //switched to branch to see “person_follower_commands” and “files.sh”
$ :~/catkin_ws/src/myo_gesture_controller/script$ ls person_follower_commands
    //included:
    // face_person.sh; 
    // follow_person.sh;
    // mute_myo_command.sh;
    // stand_still.sh 
$ :~/catkin_ws/src/myo_gesture_controller/script$ cat person_follower_commands/face_person.sh  
    //rostopic pub /myo_raw_myo_gest_str std_msgs/String “data: ‘WAVE_OUT’”
$ :~/catkin_ws/src/myo_gesture_controller/script$ rosrun myo_gesture_controller face_person.sh
    //press Ctrl_C to terminate
$ :~/catkin_ws/src/myo_gesture_controller/script$ rosrun myo_gesture_controller stand_still.sh
    //publishing and latching massage. Press ctrl-C to terminate
$ :~/catkin_ws/src/myo_gesture_controller/script$ cd
```
 
scp and errors
To copy a file from B to A while logged into B:
```
$ scp /path/to/file username@a:/path/to/destination
```
To copy a file from B to A while logged into A:
```
$ scp username@b:/path/to/file /path/to/destination
```
```
error:
username@IP Address: from nuc to lab: connection refused
```
So try from username@IP Address to username@IP Address
```
error:
no regular file
$ scp -r root@IP:/path/to/file /path/to/filedestination
```
```
right solution:
$ username@IP Address:~$ scp -r /home/caris/catkin_ws/src/vision_visp username@IP Address:/home/nuc/catkin_ws/src
```
 
Internet Connection Problem in UBC 
192.168.0.1
OR 
1.1.1.1

Joystick
It works without below command

```
$ Sudo bash
```
If powerbot_nav is not running or any package, joystick doesn’t work.
First run package which is included joystick package
ROSTopic
If no package is not running, there is no topic to show. So, run package.
```
$ Rostopic list | grep (what we want to search) 
$ Rostopic list | grep rgb
```
.
.
Error: Unable to connect with master
For “master error” in “rostopic”, 
```
$ Echo $ROS_MASTER_URI
http://localhost:...
$ ping lacalhost
```
Lasor Error
The laser button near to on and off button of powerbot. We should turn it on. 
Package Error
1. mistype the (name of node), like: start_powerbot_person_follower_controller.sho instead of start_powerbot_person_follower_controller.sh
```
$ Rosrun (name of package: myo_...) (name of node: Start_...)
.
.
.
```
Error: Failed to connect to Mir: Failed to connect to server socket:
       Unable to init server
       Failed to parse argument
2. For “master error” in “rostopic”, 
```
$ Rosrun (name of package: myo_...) (name of node: Start_...)
.
.
[rosrun] couldn’t find executable named start_..._controller.sho
Solution:
$ Echo $ROS_MASTER_URI
http://localhost:......
$ ping localhost
```
Another package:
3. restart it again. Sometimes it is because of connection to master ros.
 Open new terminal
 Write capital x “-X” in “ssh -X username@IP Address”
```
$ Rosrun rviz rviz -d tracking_right_realsense_link_nav.rviz
.
.
```
Error: Couldn’t connect to display
Clean ros log
```
$ rosclean purge
```

A QR code tracking package for  (1 try- ros_qr_tracker) 
Install dependencies:
```
$ sudo apt-get install libffi-dev libffi6 libzbar-dev python-catkin-pkg
$ pip install libzbar-cffi 
 //wrong way
```
[Errno 13] Permission denied: '/usr/local/bin/pip'
Solution:
```
$ pip install --user <package you want to install> 
```
So:
```
$  pip install --user libzbar-cffi 
```
Overlaying with a catkin Workspace
1) by creating a folder (directory) to hold the new workspace and prepare the src folder, which will store the urls and versions of sources you download
```
$  mkdir -p overlay_ws/src
$  cd overlay_ws/src 
```
2) Adding Packages to Your catkin Workspace. add a ros package from source to your src folder.
Create symlink “/home/nuc/overlay_ws/src/CMakeLists.txt”…
```
$  catkin_init_workspace 
 //create CMakeLists.txt in /overlay_ws/scr
$ git clone https://github.com/chrisspen/ros_qr_tracker.git 
 //download and create ros_qr_tracker 
```
3) Building Your catkin Workspace
```
wrong way:
$ cd ..
$ catkin_make --pkg ros_qr_tracker 
```
error: socket.error connection refused
```
Path: username@IP Address: ~/overlay_ws/src/ros_qr_tracker
```

error: no package
solution: ## THIS IS THE CRUCIAL PART FOR OVERLAYING
```
$ source ~/overlay_ws/devel/setup.bash
cd ..
catkin_make –pkg ros_qr_tracker
```
Running QR package by me in overlay_ws
First running demo packages
Find ros package
First, we should run demo to see which topics is used. Then used in our new package.
```
$ rostopic list | grep rgb
.
.
 //right_realsense/rgb/image_raw
$ rospack find ros_qr_tracker
 //[rospack] Error: package not found
$ roscd 
 //catkin_ws/devel$
 //there is no source of my package “overlay_ws”
$ catkin_ws/devel$ cd
$ source overlay_ws/
 //-bash: source: overlay_ws/: is a directory
$ source overlay_ws/devel
 //-bash: source: overlay_ws/devel: is a directory
$ source overlay_ws/devel/setup.bash
 //ignore other workspaces
$ roscd
 //overlay_ws/devel
$ overlay_ws/devel$ cd
$ vi .bashrc
$ source .bashrc
$ roscd
$ overlay_ws/devel$ vi .bashrc
$ overlay_ws/devel$ cd
$ vi .bashrc
$ gedit .bashrc //all terminals and workspace setting. Put# for my source
$ gedit /home/nuc/.bashrc
$ roscd ros_qr_tracker
 //overlay_ws/src/ros_qr_tracker
$ overlay_ws/src/ros_qr_tracker$ cd
$ rosrun ros_qr_tracker qr_tracker.py _topic:=/right_realsense/rgb/imge_raw 
 //topic from demo and rgb, mentioned before in rostopic
In another terminal
$ rosservice call /qr_tracker/start
 //Error subscriber and publisher
```

Overlay_ws instead of catkin_ws
```
$ vi .bashrc
Add #source /home/nuc/overlay_ws/devel/setup.bash
```

QR code 
Visp_auto_tracker cannot open model file ```#42```
```
ERROR: cannot launch node of type [visp_tracker/tracker]: can't locate node [tracker] in package [visp_tracker]
ERROR: cannot launch node of type [visp_tracker/visp_tracker_client]: can't locate node [visp_tracker_client] in package [visp_tracker]
ERROR: cannot launch node of type [visp_tracker/visp_tracker_viewer]: can't locate node [visp_tracker_viewer] in package [visp_tracker]
```
Solution: 
The best is to remove all ros-hydro-visp* packages, and then install the packages from source. For visp auto tracker (you can use the master branch)
```
$ cd ~/catkin_ws/src
$ cd ~/catkin_ws/src
$ git clone https://github.com/lagadic/vision_visp.git
$ cd ..
$ catkin_make --pkg visp_auto_tracker
$ source devel/setup.bash
```
```
$ cd catkin_ws/src/vision_visp/visp_auto_tracker/launch$ roslaunch visp_auto_tracker tracklive_usb.launch
```
Error:
```
cannot launch node of type [usb_cam/usb_cam_node]: usb_cam
ROS path …
```
Solution:
```
$ rospack find usb_cam
```
```
$ cd catkin_ws/src
$ catkin_init_workspace
$ firefox
  // connect to ubcvisitor
$ git clone “site address of usb_cam”
$ source ~/catkin_ws/devel/setup.bash
$ cd ..
$ catkin_make -pkg usb_cam
$ cd src
$ source ~/catkin_ws/devel/setup.bash
```
Configuration for usb_cam:
```
$ cd holobot_ros/launch
$ cat track_robot.launch
```
Error: 
```
cannot launch node of type [usb_cam/usb_cam_node]: usb_cam
```
Based on [issues of vision_visp](https://github.com/lagadic/vision_visp/issues/42)
Guidelines
Read: readme (git status, git checkout kinetic or master)
Read: cat cmake.txt! (distribution!!)
Errors:
Couldn’t install from the source. So, it can be just updated and then be installed based on the website.
For workspace existed on nuc (catkin_ws) instead of 
```
$ catkin_make --pkg “” catkin build “”
```
```
$ rospack list | grep visp 
  // search
$ rosnode list
$ rostopic list
$ roslaunch visp_auto_tracker tracklive_usb.launch
$ rostopic info /visp_auto/object_position
$ rostopic echo /visp_auto/object_position 
```
1. Config file
2. Try which topic and measure and try again
3. check packages and files
```
$ roscd visp_auto_tracker
 //find the package
$ cd launch
$ cat tracklive_usb.launch
 //change this part if I want to use realsense
 //remap from=”name of package/topic” to=”…”
 //remap from=”visp_auto_tracker/camera_info” to=“/usb_cam/camera_info” 
```
```
$ roscd person_follower
$ cat /launch/person_follower.launch
```
```
$ roscd myo_gesture_controller
$ cd scripts
$ cat start_powerbot_person_follower_controller.sh
 //including .sh and launch and a node file
```
```
$ rosed person_follower spencer_person_follower.py
 //search subscribe with “/subsc”
 //search /cmd_vel
 //subscriber (topic) type
 //pose stamp (header)
 //wesley and person follower detector 
 //it transfer position to nearest person to follow
```
```
//side walk navigation and using for move_base goal
$ roscat powerbot_nav powerbot_nav_with_people_tracker.launch
$ roscat powerbot_nav cmd_vel_mux.yaml
//right way
$ cd sidewalk_navigation/simulation/simulation_ros_catkin_ws/src/pm_robot/launch
$ cat powerbot_ubc_caris.launch
//write node: subscribe topic QR code 
//Transfer frame camera to the world
```
```
Lsusb (all deskonkey)
Dmesg (last massage connected or not)
```
Find a file
```
Find derectory -name ‘*.h’
find . -name ‘*.h’
Find geometry_msgs/ -name Twist.h
```
