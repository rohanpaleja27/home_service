/* /*
 * Copyright (c) 2010, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
/*
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/UInt8.h>

//initialize global variable keeping track of the current search phase
uint8_t cycle = 0;

// Define destination subscriber callback to set the search phase to the received value
void pickupDropoffCallback(const std_msgs::UInt8::ConstPtr& msg)
{
   ROS_INFO("Received message!");
   ROS_INFO("Message is: %d ", msg->data);
   cycle = msg->data;
   return;
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(5);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber location_sub = n.subscribe("/destination_reached", 1, pickupDropoffCallback);
  bool done = false;

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;
  cycle=0;
  while (ros::ok())
  {
    //Do this every cycle to ensure the subscriber receives the message
    ros::spinOnce();

    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;
    
    // Search phase based on receipt of message from pick_objects_node
    switch (cycle)
    {
      // Currently moving towards first goal, display this goal marker
      case 0:
        ROS_INFO_ONCE("Adding object for picking");
        marker.action = visualization_msgs::Marker::ADD;
        marker.pose.position.x = 1.0;
        marker.pose.position.y = 1.0;
        marker.pose.position.z = 0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;
        cycle += 1;
        break;

      // Reached first goal, delete the goal marker
      case 1:
        ROS_INFO_ONCE("Deleting object");
        marker.action = visualization_msgs::Marker::DELETE;
        cycle += 1;
        break;

      // Waiting to reach second goal...
      case 2:
        marker.action = visualization_msgs::Marker::DELETE;
        break;

      // Reached second goal, display marker here
      case 3: 
        ROS_INFO_ONCE("Placing object at drop-off location");
        marker.action = visualization_msgs::Marker::ADD;
        marker.pose.position.x = 0;
        marker.pose.position.y = 0;
        marker.pose.position.z = 0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;
        done = true;
        break;
    }

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.4;
    marker.scale.y = 0.4;
    marker.scale.z = 0.4;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 1.0f;
    marker.color.g = 1.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0;
    marker.lifetime = ros::Duration();
    
    // Publish the marker
    /*
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
*/
/*
    //publish the marker
    marker_pub.publish(marker);
    sleep(10);

    // if last marker published and noted as done exit
    if (done)
      return 0;

    r.sleep();
  }
  return 0;
}
*/
/*
 * Copyright (c) 2010, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <cmath>


// Define Pickup and Dropoff as global variables
#define PICKUP_X 0.0
#define PICKUP_Y 3.0

#define DROPOFF_X -1.0
#define DROPOFF_Y 0.0

//epsilon value
#define DELTA .2

bool pickup = true;
bool dropoff = false;

ros::Publisher marker_pub;
visualization_msgs::Marker marker;
//Every time message is received this will happen
void odomCallback(const nav_msgs::Odometry::ConstPtr& msg) {
 // Get x and y position from msg and print them
  float odom_x = msg->pose.pose.position.x;
  float odom_y = msg->pose.pose.position.y;
  ROS_INFO("ODOM RECIEVED, ROBOT AT X=%f, Y= %f",odom_x,odom_y);
  float delx;
  float dely;
  float dist;
  //Till pickup happens, dropoff loop doesnt start
  if (pickup) {
    delx = odom_x - PICKUP_X;
    dely = odom_y - PICKUP_Y;
    dist = std::sqrt(delx*delx+dely*dely);  //least squares dist
    ROS_INFO("Distance to pickup = %f", dist);
    if (dist < DELTA && pickup) 
    {
      ROS_INFO("Reached Pickup Point");

      // Issue pickup-delete marker
      marker.action = visualization_msgs::Marker::DELETE;
      marker_pub.publish(marker);

      // Wait 5 seconds before trying to show other markers
      ros::Duration(5.0).sleep();

      pickup = false;
      dropoff = true;
      return;
    }

  } else if (dropoff) {


    delx = odom_x - DROPOFF_X;
    dely = odom_y - DROPOFF_Y;
    dist = std::sqrt(delx*delx+dely*dely);
    ROS_INFO("Dropoff distance = %f", dist);

    if (dist < DELTA) {
      // we are at the pickup location
      ROS_INFO("Reached Dropoff Point");

      marker.pose.position.x = DROPOFF_X;
      marker.pose.position.y = DROPOFF_Y;

      marker.action = visualization_msgs::Marker::ADD;
      marker_pub.publish(marker);

      ros::Duration(5.0).sleep();
      pickup = false;
      dropoff = false;
      return;
    }
  }

}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;


  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);


  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "/map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "basic_shapes";
  marker.id = 0;

  // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  uint32_t shape = visualization_msgs::Marker::CUBE;
  marker.type = shape;
  marker.action = visualization_msgs::Marker::ADD;

  // Set location of marker
  marker.pose.position.x = PICKUP_X;
  marker.pose.position.y = PICKUP_Y;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;

  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = 0.5;
  marker.scale.y = 0.5;
  marker.scale.z = 0.5;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.4f;
  marker.color.g = 0.4f;
  marker.color.b = 1.0f;
  marker.color.a = 1.0;

  marker.lifetime = ros::Duration();

  ros::Duration(1.0).sleep();
  //Command will show whatever marker if statement says to show
  ROS_INFO("Adding marker");
  marker_pub.publish(marker);
  /*
  // This is the way used in the add_markers.sh method
  ROS_INFO("Wait 5 seconds");
  ros::Duration(5.0).sleep();
  marker.action = visualization_msgs::Marker::DELETE;
  ROS_INFO("Removing marker");
  marker_pub.publish(marker);
  ROS_INFO("Wait 5 seconds");
  ros::Duration(5.0).sleep();
  // Show marker at the dropoff location
  marker.pose.position.x = DROPOFF_X;
  marker.pose.position.y = DROPOFF_Y;
  marker.pose.position.z = 0;
  marker.action = visualization_msgs::Marker::ADD;
  ROS_INFO("Adding marker at drop off zone");
  marker_pub.publish(marker);
  */



  ros::Subscriber odom_sub = n.subscribe("/odom", 1, odomCallback);


  ros::Rate r(10.0); // 10 Hz
  while (ros::ok()) {
      ros::spinOnce();
      r.sleep();
  }

  return 0;

}

