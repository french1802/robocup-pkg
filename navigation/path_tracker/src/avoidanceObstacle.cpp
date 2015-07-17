/**
 * \file         avoidanceObstacle.cpp
 *
 * \brief
 *
 * \author       Tissot Elise (elise.tissot@polytech-lille.net)
 * \date         2015-07-08
 * \copyright    PyroTeam, Polytech-Lille
 * \license
 * \version
 */

#include "avoidanceObstacle.h"

/* Constantes */
#define DIST_POINTS_PATH  0.05
#define VIT_ANGLE_MAX     30
#define TIME_OBSTACLE     5
#define DIST_MAX          3

float AvoidanceObstacle::calculDistance(geometry_msgs::Point point1, geometry_msgs::Point point2)
{
    return sqrt((point1.x - point2.x)*(point1.x - point2.x) + (point1.y - point2.y)*(point1.y - point2.y));
}

geometry_msgs::Point AvoidanceObstacle::calculPointsPath(geometry_msgs::Point pointD, geometry_msgs::Point pointA)
{
    float a = (pointA.y - pointD.y)/(pointA.x - pointD.x);
    float b = pointA.y - a * pointA.x;
    float xO = pointD.x;
    float yO = pointD.y;
    float delta = 0;
    geometry_msgs::Point point;

    // Intersection entre une droite et un cercle
    delta = 2*(a*(b-yO)-xO)*2*(a*(b-yO)-xO) - 4*(1+a*a)*(xO*xO+(b-yO)*(b-yO)-DIST_POINTS_PATH*DIST_POINTS_PATH);

    if (delta > 0)
    {
        geometry_msgs::Point point1;
        point1.x = (-2*(a*(b-yO)-xO) + sqrt(delta)) / (2*(1+a*a));
        point1.y = a*point1.x + b;
        geometry_msgs::Point point2;
        point2.x = (-2*(a*(b-yO)-xO) + sqrt(delta)) / (2*(1+a*a));
        point2.y = a*point2.x + b;

        if (calculDistance(pointA, point1) < calculDistance(pointA, point2))
        {
            point.x = point1.x;
            point.y = point1.y;
        }
        else
        {
            point.x = point2.x;
            point.y = point2.y;
        }
    }
    else if (delta == 0)
    {
        point.x = (-2*(a*(b-yO)-xO)) / (2*(1+a*a));
        point.y = a*point.x + b;
    }
    else // delta < 0
    {
        ROS_INFO("Erreur points chemin");
    }
    return point;
}

float AvoidanceObstacle::normaliseAngle(float angle)
{
    float angleNormalise = angle;
    while (angleNormalise <= -M_PI)
    {
        angleNormalise += 2 * M_PI;
    }
    while (angleNormalise > M_PI)
    {
        angleNormalise -= 2 * M_PI;
    }
    return angleNormalise;
}

void AvoidanceObstacle::track(geometry_msgs::Point point, geometry_msgs::Point pointSuiv, geometry_msgs::Pose odom)
{
    float dx = pointSuiv.x - point.x;
    float dy = pointSuiv.y - point.y;
    float ang = atan2(dy, dx);

    float adj = point.x - odom.position.x;
    float opp = point.y - odom.position.y;
    float angle = atan2(opp, adj);
    float yaw = tf::getYaw(odom.orientation);

    float errAngle = (angle - yaw);
    errAngle = normaliseAngle(errAngle);

    float errAnglePointSuiv = (ang - yaw);
    errAnglePointSuiv = normaliseAngle(errAnglePointSuiv);

    float vitAngle = errAnglePointSuiv * 1;

    if (vitAngle > VIT_ANGLE_MAX)
    {
        vitAngle = VIT_ANGLE_MAX;
    }
    else if (vitAngle < -VIT_ANGLE_MAX)
    {
        vitAngle = -VIT_ANGLE_MAX;
    }
    m_cmdVel.linear.x = 0.2;
    m_cmdVel.linear.y = errAngle/10;
    m_cmdVel.angular.z = vitAngle*1;
    m_cmdVel_pub.publish(m_cmdVel);
}

void AvoidanceObstacle::avoid(const nav_msgs::OccupancyGrid &grid, const geometry_msgs::Pose &odom, std::vector<geometry_msgs::PoseStamped> &path, actionlib::SimpleActionServer<deplacement_msg::TrackPathAction> &as, deplacement_msg::TrackPathFeedback &feedback)
{
    m_dataMapObstacle.calculObstacle(odom, path);
    std::vector<geometry_msgs::Point> vectorObstacle = m_dataMapObstacle.getVectorObstacle();
    ROS_INFO("Taille vector obstacles : %d", vectorObstacle.size());

    geometry_msgs::Point pointTarget;
    if (vectorObstacle.size() == 0)
    {
        ROS_INFO("Erreur taille obstacle");
        return;
    }
    pointTarget = vectorObstacle[0];
    for (int i = 1 ; i < vectorObstacle.size() ; i++)
    {
        if (calculDistance(m_dataMapObstacle.getPointPathObstacle(), vectorObstacle[i]) > calculDistance(m_dataMapObstacle.getPointPathObstacle(), pointTarget))
        {
            pointTarget = vectorObstacle[i];
        }
    }
    ROS_INFO("Point à atteindre : x = %f, y = %f", pointTarget.x, pointTarget.y);

    float distRobot = calculDistance(odom.position, pointTarget);
    int nbPoints = distRobot/DIST_POINTS_PATH;

    // On construit le chemin jusqu'au point extrême
    geometry_msgs::Point pointD = odom.position;
    geometry_msgs::Point point;
    geometry_msgs::PoseStamped poseStamped;
    while (nbPoints > 0)
    {
        point = calculPointsPath(pointD, m_pointArrival);
        poseStamped.pose.position = point;
        m_intermediatePath.push_back(poseStamped);
        pointD = point;
        nbPoints--;
    }
    ROS_INFO("Chemin construit");
    ROS_INFO("Nb points chemin : %d", m_intermediatePath.size());

    // On le suit
    int i = 0;
    while (i < m_intermediatePath.size() && !m_failure)
    {
        m_dataMapObstacle.calculObstacle(odom, m_intermediatePath);
        if (m_dataMapObstacle.getObstacle())
        {
            m_cmdVel.linear.x = 0;
            m_cmdVel.linear.y = 0;
            m_cmdVel.angular.z = 0;

            m_failure = true;
            ROS_INFO("Echec evitement");

            /*ros::Time t = ros::Time::now() + ros::Duration(TIME_OBSTACLE);
            while (m_dataMapObstacle.getObstacle() && ros::Time::now() < t)
            {
                m_dataMapObstacle.calculObstacle(odom, m_intermediatePath);
            }
            if (ros::Time::now() == t)
            {
                m_failure = true;
            }*/
        }
        else
        {
            geometry_msgs::Point pointSuiv;
            if (m_intermediatePath.size() >= 2)
            {
                pointSuiv = m_intermediatePath[i+1].pose.position;
            }
            else
            {
                pointSuiv = m_intermediatePath[i].pose.position;
            }
            track(m_intermediatePath[i].pose.position, pointSuiv, odom);
            feedback.distance_path = calculDistance(odom.position, path[0].pose.position);
            as.publishFeedback(feedback);
            i++;
        }
    }
    if (m_failure)
    {
        return;
    }
    ROS_INFO("Premiere partie evitement reussie");
    // Sinon on est arrivé à destination
    // On regarde à présent si le chemin initial est atteignable
    while (!m_successAvoidance && !m_failure)
    {
        std::vector<geometry_msgs::PoseStamped> &pathGenerating = path;
        while (pathGenerating.size() > 0 && m_dataMapObstacle.getObstacle())
        {
            m_dataMapObstacle.calculObstacle(odom, pathGenerating);
            if (m_dataMapObstacle.getObstacle())
            {
                pathGenerating.erase(pathGenerating.begin());
            }
        }
        if (pathGenerating.size() == 0 /*|| calculDistance(odom.position, path[j].pose.position) > DIST_MAX*/)
        {
            ROS_INFO("Obstacle non entierement contourne");
            vectorObstacle = m_dataMapObstacle.getVectorObstacle();
            if (vectorObstacle.size() == 0)
            {
                ROS_INFO("Erreur taille obstacle");
                return;
            }
            /*m_pointArrival = vectorObstacle[0];
            for (int i = 1 ; i < vectorObstacle.size() ; i++)
            {
                if (calculDistance(m_dataMapObstacle.getPointPathObstacle(), vectorObstacle[i]) > calculDistance(m_dataMapObstacle.getPointPathObstacle(), m_pointArrival))
                {
                    m_pointArrival = vectorObstacle[i];
                }
            }
            distRobot = calculDistance(odom.position, m_pointArrival);
            nbPoints = distRobot/DIST_POINTS_PATH;*/
            m_failure = true;
            ROS_INFO("Echec evitement");
        }
        else // On peut atteindre le chemin généré par le pathfinder
        {
            ROS_INFO("On rejoint le chemin");
            m_almostDone = true;
            m_pointArrival = path[0].pose.position;
            distRobot = calculDistance(odom.position, path[0].pose.position);
            nbPoints = distRobot/DIST_POINTS_PATH;
        }
        ROS_INFO("Point a atteindre : x = %f, y = %f", m_pointArrival.x, m_pointArrival.y);
        while (nbPoints > 0)
        {
            point = calculPointsPath(pointD, m_pointArrival);
            poseStamped.pose.position = point;
            m_intermediatePath.push_back(poseStamped);
            pointD = point;
            nbPoints--;
        }

        // On le suit
        i = 0;
        while (i < m_intermediatePath.size() && !m_failure)
        {
            m_dataMapObstacle.calculObstacle(odom, m_intermediatePath);
            if (m_dataMapObstacle.getObstacle())
            {
                m_cmdVel.linear.x = 0;
                m_cmdVel.linear.y = 0;
                m_cmdVel.angular.z = 0;

                m_failure = true;
                ROS_INFO("Echec evitement");

                /*ros::Time t = ros::Time::now() + ros::Duration(TIME_OBSTACLE);
                while (m_dataMapObstacle.getObstacle() && ros::Time::now() < t)
                {
                    m_dataMapObstacle.calculObstacle(odom, m_intermediatePath);
                }
                if (ros::Time::now() == t)
                {
                    m_failure = true;
                }*/
            }
            else
            {
                geometry_msgs::Point pointSuiv;
                if (m_intermediatePath.size() >= 2)
                {
                    pointSuiv = m_intermediatePath[i+1].pose.position;
                }
                else
                {
                    pointSuiv = m_intermediatePath[i].pose.position;
                }
                track(m_intermediatePath[i].pose.position, pointSuiv, odom);
                feedback.distance_path = calculDistance(odom.position, path[0].pose.position);
                as.publishFeedback(feedback);
                i++;
            }
        }
        if (m_almostDone && !m_failure)
        {
            /*int k = 0;
            while (k < j)
            {
                path.erase(path.begin());
                k++;
            }*/
            path = pathGenerating;
            m_successAvoidance = true;
            ROS_INFO("Evitement reussi");
        }
    }
}

void AvoidanceObstacle::resetMode()
{ 
    m_failure = false;
    m_successAvoidance = false;
}

bool AvoidanceObstacle::failure()
{
    return m_failure;
}

bool AvoidanceObstacle::successAvoidance()
{
    return m_successAvoidance;
}
