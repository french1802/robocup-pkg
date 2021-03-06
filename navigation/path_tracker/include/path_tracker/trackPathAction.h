/**
 * \file         trackPathAction.h
 *
 * \brief
 *
 * \author       Tissot Elise (elise.tissot@polytech-lille.net)
 * \date         2015-06-15
 * \copyright    2016, Association de Robotique de Polytech Lille All rights reserved
 * \version
 */

#ifndef TRACKPATHACTION_H
#define TRACKPATHACTION_H

#include <iostream>
#include <vector>
#include <list>

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>

//#include "trackPath.h"
#include "avoidanceObstacle.h"

#include "deplacement_msg/TrackPathAction.h"
#include "pathfinder/AstarPath.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/PoseStamped.h"
#include "sensor_msgs/LaserScan.h"

/* Constantes */
#define SIZE_LIST 10

class TrackPathAction
{
private:
    ros::Subscriber m_path_sub;
    ros::Subscriber m_odom_sub;

    bool m_success;
    bool m_failure;
    int m_mode;
    ros::Time m_timePath;
    ros::Time m_timeAvoidance;
    int m_pointsPath;

    struct Path
    {
        int m_path_id;
        std::vector<geometry_msgs::PoseStamped> m_path_points;
    };

    std::list<Path> m_path;
    geometry_msgs::Pose m_odom_pose;
    
    TrackPath m_pathTrack;
    AvoidanceObstacle m_avoidObstacle;
    DataMapObstacle m_dataMapObstacle;

    void pathCallback(const pathfinder::AstarPath &path);
    void odomCallback(const nav_msgs::Odometry &odom);

    ros::NodeHandle m_nh;
    actionlib::SimpleActionServer<deplacement_msg::TrackPathAction> m_as;
    std::string m_action_name;
    deplacement_msg::TrackPathFeedback m_feedback;
    deplacement_msg::TrackPathResult m_result;

    float calculDistance(geometry_msgs::Point point1, geometry_msgs::Point point2);

public:
    TrackPathAction(std::string name) : m_as(m_nh, name, boost::bind(&TrackPathAction::executeCB, this, _1), false), m_action_name(name)
    {
        m_mode = 3;
        m_pointsPath = 0;

        m_odom_sub = m_nh.subscribe("hardware/odom", 1, &TrackPathAction::odomCallback, this);
        m_path_sub = m_nh.subscribe("navigation/pathFound", 1, &TrackPathAction::pathCallback, this);
        m_success = false;
        m_failure = false;
        m_as.start();
    }

    ~TrackPathAction()
    {
    }

    void executeCB(const deplacement_msg::TrackPathGoalConstPtr &goal);
};

#endif /*TRACKPATHACTION_H*/
