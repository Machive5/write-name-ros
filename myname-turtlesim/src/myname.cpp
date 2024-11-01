#include <stdio.h>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Kill.h>
#include <turtlesim/Spawn.h>
#include <turtlesim/SetPen.h>
#include <turtlesim/TeleportAbsolute.h>


using namespace std;
using namespace ros;

void go(float x, float y, float theta, Publisher pub){
    Rate loop_rate(1);

    geometry_msgs::Twist msg;
    msg.linear.x = x;
    msg.linear.y = y;
    msg.angular.z = theta*M_PI/180;

    pub.publish(msg);
    spinOnce();
    loop_rate.sleep();
}

void penUp(float x, float y, float theta, NodeHandle handler){
    ServiceClient client = handler.serviceClient<turtlesim::Kill>("/kill",1);
    turtlesim::Kill kill;
    kill.request.name = "turtle1";
    client.call(kill);
    spinOnce();

    Rate loop_rate(1);

    client = handler.serviceClient<turtlesim::Spawn>("/spawn",1);
    turtlesim::Spawn spawn;
    spawn.request.name = "turtle1";
    spawn.request.x = x;
    spawn.request.y = y;
    spawn.request.theta = theta*M_PI/180;
    client.call(spawn);
    
    spinOnce();
    loop_rate.sleep();
}

int main (int argc, char** argv){
    init(argc, argv, "myname");

    NodeHandle nh;
    Publisher pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",1);
    Rate loop_rate(2);
    loop_rate.sleep();
    //R
    penUp(1,4,0,nh);
    go(0,1.5,0,pub);
    go(0.5,0,0,pub);
    go(1.179,0,-180,pub);
    go(0.5,0,0,pub);
    go(0,0,135,pub);
    go(0.75/cos(45*M_PI/180),0,0,pub);

    //A
    penUp(2.5,4,0,nh);
    go(0,0,71,pub);
    go(1.58,0,0,pub);
    go(0,0,-142,pub);
    go(1.58,0,0,pub);
    penUp(2.5,4.5,0,nh);
    go(1,0,0,pub);

    //F
    penUp(4,4,0,nh);
    go(0,1.5,0,pub);
    go(1,0,0,pub);
    penUp(4,4.75,0,nh);
    go(1,0,0,pub);

    // I
    penUp(5.5,4,0,nh);
    go(0,1.5,0,pub);

    // dot
    penUp(6,4.5,0,nh);
    go(1,0,360,pub);

    //C
    penUp(7.75,4,180,nh);
    go(0.5,0,0,pub);
    go(2.357,0,-180,pub);
    go(0.5,0,0,pub);

    //E
    penUp(9.25,4,180,nh);
    go(1,0,0,pub);
    go(0,-1.5,0,pub);
    go(-1,0,0,pub);
    penUp(9.25,4.75,0,nh);
    go(-1,0,0,pub);

    //border
    penUp(0.5,3.5,0,nh);
    go(10,0,0,pub);
    go(0,2.5,0,pub);
    go(-10,0,0,pub);
    go(0,-2.5,0,pub);

    //segi enam
    penUp(2,9,0,nh);
    for (int i = 1; i<=6; i++){
        go(0.5,0,0,pub);
        go(0,0,60,pub);
    }
    
    //segi 8
    penUp(4,7,0,nh);
    for (int i = 1; i<=8; i++){
        go(0.5,0,0,pub);
        go(0,0,45,pub);
    }

    //bintang kecil
    penUp(8,8,0, nh);
    for (int i = 1; i<=5; i++){
        go(2,0,0,pub);
        go(0,0,144,pub);
    }

    //circle
    penUp(6,8.5,0, nh);
    go(6,0,360,pub);

    //gelombang laut pasang
    penUp(0,1.5,0, nh);
    ServiceClient wave = nh.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute",1);

    for (float i = 0; i<11; i+=0.1){
        turtlesim::TeleportAbsolute msg;
        msg.request.x = i;
        msg.request.y = sin(2*i)+1.5;
        wave.call(msg);
        spinOnce();
    }

    

    return 0;
}