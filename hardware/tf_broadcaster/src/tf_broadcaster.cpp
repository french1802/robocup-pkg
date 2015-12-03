#include "tf_broadcaster/tf_broadcaster.h"

void poseCallback(const nav_msgs::Odometry &odom)
{
    static tf::TransformBroadcaster mapToOdom;
    static tf::TransformBroadcaster odomToBaseLink;
    static tf::TransformBroadcaster baseLinkToLaserLink;
    static tf::TransformBroadcaster baseLinkToTowerCameraLink;
    static tf::TransformBroadcaster baseLinkToPlatformCameraLink;
    static ros::NodeHandle nh;

    std::string tf_prefix;
    nh.param<std::string>("simuRobotNamespace", tf_prefix, "");;
    if (tf_prefix.size() != 0)
        tf_prefix += "/";

    // Map to odom
    tf::Transform transform;
    transform.setOrigin(tf::Vector3(0.0, 0.0, 0.0));
    tf::Quaternion q;
    q.setRPY(0.0, 0.0, 0.0);
    transform.setRotation(q);
    mapToOdom.sendTransform(tf::StampedTransform(transform, odom.header.stamp, "map", tf_prefix+"odom"));

    // Odom to Base Link
    transform.setOrigin(tf::Vector3(odom.pose.pose.position.x, odom.pose.pose.position.y, 0.0));
    tf::quaternionMsgToTF(odom.pose.pose.orientation, q);
    transform.setRotation(q);
    odomToBaseLink.sendTransform(tf::StampedTransform(transform, odom.header.stamp, tf_prefix+"odom", tf_prefix+"base_link"));

    // Base Link to Laser Link
    static double laser_link_x = 0;
    nh.param<double>("hardware/robotDescription/baseLink_to_laserLink/x", laser_link_x, 0.10);
    transform.setOrigin(tf::Vector3(laser_link_x, 0.0, 0.232));
    q.setRPY(0.0, 0.0, 0.0);
    transform.setRotation(q);
    baseLinkToLaserLink.sendTransform(tf::StampedTransform(transform, odom.header.stamp, tf_prefix+"base_link", tf_prefix+"laser_link"));

    // Base Link to Tower Camera Link
    static double tower_camera_link_z = 0;
    nh.param<double>("hardware/robotDescription/baseLink_to_towerCameraLink/z", tower_camera_link_z, 0.60);
    transform.setOrigin(tf::Vector3(0.2, 0.0, tower_camera_link_z));
    q.setRPY(0.0, 0.0, 0.0);
    transform.setRotation(q);
    baseLinkToTowerCameraLink.sendTransform(tf::StampedTransform(transform, odom.header.stamp, tf_prefix+"base_link", tf_prefix+"tower_camera__link"));

    // Base Link to Platform Camera Link
    static double platform_camera_link_z = 0;
    nh.param<double>("hardware/robotDescription/baseLink_to_platformCameraLink/z", platform_camera_link_z, 0.90);
    transform.setOrigin(tf::Vector3(0.0, 0.0, platform_camera_link_z));
    q.setRPY(0.0, 0.0, 0.0);
    transform.setRotation(q);
    baseLinkToPlatformCameraLink.sendTransform(tf::StampedTransform(transform, odom.header.stamp, tf_prefix+"base_link", tf_prefix+"platform_camera_link"));
}