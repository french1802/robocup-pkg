/**
 * \file         trackPath.cpp
 *
 * \brief
 *
 * \author       Tissot Elise (elise.tissot@polytech-lille.net)
 * \date         2015-06-18
 * \copyright    PyroTeam, Polytech-Lille
 * \license
 * \version
 */

#include "trackPath.h"

bool TrackPath::comparePoints(geometry_msgs::Point point1, geometry_msgs::Point point2)
{
    if (point1.x != point2.x)
    {
        return false;
    }
    else
    {
        if (point1.y != point2.y)
        {
            return false;
        }
        else
        {
            if (point1.z != point2.z)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
}

geometry_msgs::Point TrackPath::closestPoint(geometry_msgs::Point segmentStart, geometry_msgs::Point segmentStop, geometry_msgs::Point point)
{
    geometry_msgs::Point closestPoint;
    float xDelta = segmentStop.x - segmentStart.x;
    float yDelta = segmentStop.y - segmentStart.y;

    if (xDelta == 0 && yDelta == 0)
    {
        closestPoint = segmentStart;
        return closestPoint;
    }

    float u = ((point.x - segmentStart.x) * xDelta + (point.y - segmentStart.y) * yDelta) / (xDelta * xDelta + yDelta * yDelta);

    if (u < 0)
    {
        closestPoint = segmentStart;
    }
    else if (u > 1)
    {
        closestPoint = segmentStop;
    }
    else
    {
        closestPoint.x = segmentStart.x + u * xDelta;
        closestPoint.y = segmentStart.y + u * yDelta;
    }
    return closestPoint;
}

void TrackPath::track(std::vector<geometry_msgs::PoseStamped> points, geometry_msgs::Pose odom)
{
    geometry_msgs::Point pose;
    geometry_msgs::Point closest;
    geometry_msgs::Point start;
    geometry_msgs::Point stop;
    geometry_msgs::Point nextPoint;
    geometry_msgs::Point pointObjectif;
    geometry_msgs::Point pointSuiv;
    pose.x = odom.position.x;
    pose.y = odom.position.y;

    if (points.size() != 0)
    {
        m_stopRobot = false;
    }
    pointObjectif = points[0].pose.position;
    for (int i = 0 ; i < points.size() ; i++)
    {
        if (points.size() >= 1)
        {
            start = points[0].pose.position;
            if (points.size() >= 2)
            {
                stop = points[1].pose.position;
                closest = closestPoint(start, stop, pose);
                if (comparePoints(closest, stop))
                {
                    points.erase(points.begin());
                    continue;
                }
                else
                {
                    break;
                }
            }
            else
            {
                closest = start;
                m_stopRobot = true;
            }
        }
    }

    // Distance d'avance
    float distAvance = 0.1;

    // Point d'avance
    geometry_msgs::Point pointAvance;

    if (points.size() >= 2)
    {
        pointSuiv = points[1].pose.position;
    }
    else
    {
        pointSuiv = points[0].pose.position;
    }

    float dx = pointSuiv.x - closest.x;
    float dy = pointSuiv.y - closest.y;
    float ang = atan2(dy, dx);

    pointAvance.x = closest.x + distAvance * cos(ang);
    pointAvance.y = closest.y + distAvance * sin(ang);

    // Rejoindre le point d'avance
    float adj = pointAvance.x - odom.position.x;
    float opp = pointAvance.y - odom.position.y;
    float angle = atan2(opp, adj);

    float yaw =tf::getYaw(odom.orientation);

    float errAngle = (angle - yaw);
    errAngle = ((errAngle + M_PI) / (2 * M_PI)) - M_PI;

    float errAnglePointSuiv = (ang - yaw);
    errAnglePointSuiv = ((errAnglePointSuiv + M_PI) / (2 * M_PI)) - M_PI;

    float vitAngle = errAnglePointSuiv * 1;

    if (vitAngle > 30)
    {
        vitAngle = 30;
    }
    else if (vitAngle < -30)
    {
        vitAngle = -30;
    }

    if (!m_stopRobot)
    {
        m_cmdVel.linear.x = 0.2;
        m_cmdVel.linear.y = errAngle/10;
        m_cmdVel.angular.z = vitAngle*1;
    }
    else
    {
        m_cmdVel.linear.x = 0;
        m_cmdVel.linear.y = 0;
        m_cmdVel.angular.z = 0;
    }
    m_cmdVel_pub.publish(m_cmdVel);
}

bool TrackPath::success()
{
    return m_success;
}

bool TrackPath::failure()
{
    return m_failure;
}
