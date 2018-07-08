#!/bin/sh

catkin_src_dir=/home/workspace/catkin_ws/src

xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$catkin_src_dir/World/Ushaped3.world" &
sleep 5

xterm -e "roslaunch turtlebot_gazebo gmapping_demo.launch custom_gmapping_launch_file:=/home/workspace/catkin_ws/src/turtlebot_simulator/turtlebot_gazebo/launch/gmapping.launch.xml" & 
sleep 5
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; rosrun wall_follower wall_follower"
