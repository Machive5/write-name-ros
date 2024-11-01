#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <vector>
#include <turtlesim/Pose.h>

using namespace ros;
using namespace std;

void callback(const geometry_msgs::Twist msg){

    ROS_INFO("x=[%.2f] y=[%.2f] z=y=[%.2f]\n", msg.linear.x, msg.linear.y, msg.angular.z);
}

int main(int argc, char** argv){
    init(argc, argv, "subsTest");
    NodeHandle nh;
    Subscriber sub = nh.subscribe("/turtle1/cmd_vel",1, callback);
    spin();
    return 0;
}