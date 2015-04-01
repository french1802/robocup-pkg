#include "ros/ros.h"
#include "manager_msg/Landmarks.h"
#include "geometry_msgs/Pose2D.h"

#include <sstream>

int main(int argc, char **argv)
{

  ros::init(argc, argv, "talker");

  ROS_INFO("Starting publishing ");

  ros::NodeHandle n;

  ros::Publisher landmarks_pub = n.advertise<manager_msg::Landmarks>("/landmarks", 1000);

  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok())
  {
    
    ROS_INFO("test");
    std::vector<geometry_msgs::Pose2D> msg;

    while(count < 12){
      geometry_msgs::Pose2D pose;

      pose.x = count;
      pose.y = count;
      pose.theta = count;
      msg.push_back(pose);
      ++count;
    }

    manager_msg::Landmarks pub;
    pub.landmarks = msg;

    landmarks_pub.publish(pub);

    ros::spinOnce();

    loop_rate.sleep();
  }


  return 0;
}