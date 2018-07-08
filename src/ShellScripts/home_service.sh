#!/bin/sh

catkin_src_dir=/home/workspace/catkin_ws/src

xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/World/Ushaped3.world" &
sleep 5

xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/workspace/catkin_ws/src/World/mymap2.yaml" & 
sleep 5

xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e "rosrun add_markers add_markers_node" &
sleep 5

xterm -e "rosrun pick_objects pick_objects_node" &
sleep 5
