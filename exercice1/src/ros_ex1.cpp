#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Spawn.h"
#include "turtlesim/Kill.h"

//Add the required header



ros::Publisher pub;


void turtleCallback(const turtlesim::Pose::ConstPtr& msg)
	{
	ROS_INFO("Turtle subscriber@[%f, %f, %f]",  
	msg->x, msg->y, msg->theta);
	geometry_msgs::Twist my_vel;
	
	//modify the code for implementing the required behaviour
    if (msg->y > 11.0){
        my_vel.linear.x = 0;
        my_vel.angular.z = 0;}
	else if (msg->x > 9.0){
        my_vel.linear.x = 1.0;
        my_vel.angular.z = 2.0;
	}
	else if (msg->x < 1.5){
        my_vel.linear.x = 1.0;
        my_vel.angular.z = -2.0;
	}
	else{
        my_vel.linear.x = 1.0;
        my_vel.angular.z = 0.0;
	}
    pub.publish(my_vel);
    }



int main (int argc, char **argv)
{
// Initialize the node, setup the NodeHandle for handling the communication with the ROS //system  
	ros::init(argc, argv, "turtlebot_subscriber");  
	ros::NodeHandle nh;
	// Define the subscriber to turtle's position  
	pub = nh.advertise<geometry_msgs::Twist>("rpr_turtle/cmd_vel",1);  //check the topic name
	ros::Subscriber sub = nh.subscribe("rpr_turtle/pose", 1,turtleCallback);  //check the topic name

	ros::ServiceClient client1 =  nh.serviceClient<turtlesim::Spawn>("/spawn");
	//add the required client
	ros::ServiceClient client2 =  nh.serviceClient<turtlesim::Kill>("/kill");
    turtlesim::Kill srv2;
	//call the service for "killing" turtle1
    srv2.request.name = "turtle1";
    client2.call(srv2);
	
	//modify the starting position of "my_turtle"
	turtlesim::Spawn srv1;
	srv1.request.x = 2.0;  
	srv1.request.y = 1.0;
	srv1.request.theta = 0.0;
	srv1.request.name = "rpr_turtle";
	client1.call(srv1);
 
	ros::spin();
	return 0;
}