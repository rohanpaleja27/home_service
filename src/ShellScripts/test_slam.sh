#!/bin/sh
catkin_src_dir=/home/workspace/catkin_ws/src
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/World/Ushaped2.world" &
sleep 5
xterm -e "rosrun gmapping slam_gmapping" & 
sleep 5
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e "roslaunch turtlebot_teleop keyboard_teleop.launch"
