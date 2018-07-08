#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/UInt8.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle n;

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //set up publisher to broadcast if robot is at pick up location
  ros::Publisher location_pub = n.advertise<std_msgs::UInt8>("/destination_reached", 1);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal pickup;
  move_base_msgs::MoveBaseGoal dropoff;
  
  // Goal1 and 2
  pickup.target_pose.header.frame_id = "map";
  pickup.target_pose.header.stamp = ros::Time::now();
  dropoff.target_pose.header.frame_id = "map";
  dropoff.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach at each goal
  pickup.target_pose.pose.position.x = 0.0;
  pickup.target_pose.pose.position.y = 3.0;
  pickup.target_pose.pose.orientation.w = 1.0;
  dropoff.target_pose.pose.position.x = -1.0;
  dropoff.target_pose.pose.position.y = 0.0;
  dropoff.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pickup position");
  ac.sendGoal(pickup);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    ROS_INFO("Hooray, the robot reached the pickup point");
    //Wait for 5 seconds before continuing to next goal
    sleep(5);
  }
  else
  {
    ROS_INFO("The robot failed to reach the pickup point");
    return 0;
  }
  
  // Go for dropoff
  ROS_INFO("Sending the dropoff point!");
  ac.sendGoal(dropoff);
  
  // Wait an infinite time for the results
  ac.waitForResult();
  
  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    ROS_INFO("Hooray, the robot reached the dropoff point");

  }
  else
  {
    ROS_INFO("The robot failed to reach the second zone");
  }

  sleep(5);
  
  return 0;
}
