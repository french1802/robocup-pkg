#include "final_approach/ArTagFA.h"

#include <ros/ros.h>
#include <ar_track_alvar_msgs/AlvarMarkers.h>
#include <tf2/utils.h>

#include <vector>

void ArTagFA::artagCallback(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr& msg)
{
	// Cleanup
	m_foundId = false;
	m_id.clear();
	m_positionX.clear();
	m_positionZ.clear();
	m_orientationZ.clear();
	m_distance.clear();
	m_arTags.clear();

	if(!msg->markers.empty())
	{
		std::string tf_prefix;
		m_nh.param<std::string>("simuRobotNamespace", tf_prefix, "");
		if (tf_prefix.size() != 0)
			tf_prefix += "/";

		// Garantie, violemment, que l'on travaille avec les bonnes informations
		// En l'attente du changement de repère adequat, les positions ARTag doivent être publiées
		// dans le bon repère, à savoir le repère tower_camera_link du robot
		//
		// Je vous l'accorde, c'est du brutal
		if (msg->markers.front().header.frame_id.compare(tf_prefix+"tower_camera_link") != 0)
		{
			// Throttle pour le cas ou NDEBUG est défini. Dans ce cas assert sera bypassé
			// il faut tout de même avertir de l'erreur et régulièrement pour s'assurer d'être vu
			ROS_ERROR_THROTTLE(3.0, "WRONG FRAME! "
				"ARTag markers MUST be published in robotino_ns/tower_camera_link frame");
			assert(!"ARTag markers MUST be published in robotino_ns/tower_camera_link frame");
		}

		for(int i = 0; i < msg->markers.size(); i++)
		{
			arTag_t arTag;

			// XXX: A correct transform (with tf2) is needed here
			// Une fois ramené dans le repère robot (comme il se doit), le calcul de distance sera invalide
			// Idem pour l'angle. Pour rappel, sur une caméra, z pointe vers la cible, x pointe à droite, y en bas

			// XXX: Bien qu'on est censé être à même hauteur (donc y = 0), il ne faudrait pas l'oublier dans le calclul
			// A prendre en compte une fois la transformation utilisée
			float dist = sqrt(	msg->markers[i].pose.pose.position.x * msg->markers[i].pose.pose.position.x
								+ msg->markers[i].pose.pose.position.z * msg->markers[i].pose.pose.position.z);

			// On filtre les arTag trop éloignés
			if(dist < 2.0)
			{

				double roll, pitch, yaw;
				try
				{
					tf2::getEulerYPR(msg->markers[i].pose.pose.orientation, yaw, pitch, roll);
				}
				catch(tf2::TransformException ex)
				{
					ROS_ERROR("artagCallback - %s", ex.what());
				}

				arTag.id = msg->markers[i].id;
				arTag.distance = dist;
				arTag.yaw = -pitch; // XXX: C'est évidemment faux, mais l'absence de transformation amène à ça, à changer
				arTag.pose = msg->markers[i].pose.pose;

				m_arTags.push_back(arTag);

				// TODO: Replace by getter with boolean condition
				m_foundId = true;

				// XXX: Remove because useless now (thanks to m_arTags)
				m_id.push_back(msg->markers[i].id);
				m_positionX.push_back(msg->markers[i].pose.pose.position.x);
				m_positionZ.push_back(msg->markers[i].pose.pose.position.z);
				m_orientationZ.push_back(msg->markers[i].pose.pose.orientation.z);
				m_distance.push_back(dist);

				ROS_DEBUG_NAMED("investigation", "Found one TAG. id - (x, z, theta) - dist : %d - (%f, %f, %f) - %f\n"
								"(At index #%d)"
								, msg->markers[i].id
								, msg->markers[i].pose.pose.position.x
								, msg->markers[i].pose.pose.position.z
								, msg->markers[i].pose.pose.orientation.z
								, dist
								, i);

				m_stamp = msg->markers[i].header.stamp;
				m_frame = msg->markers[i].header.frame_id;
			}
		}
	}

	if(m_foundId == true)
	{
		ROS_DEBUG_NAMED("investigation","Au minimun un artag a moins de 2 m");
	}
	else
	{
		ROS_DEBUG_NAMED("investigation","No artag found");
	}
}

ArTagFA::ArTagFA()
{
	m_arTagSub = m_nh.subscribe("ar_pose_marker", 1, &ArTagFA::artagCallback, this);
}

std::vector<int> ArTagFA::getId()
{
	if(m_id.empty())
	{
		ROS_INFO("m_id.size() = %d",(int)m_id.size());
		return m_id;
	}
	else
	{
		return m_id;
	}
}

std::vector<float> ArTagFA::getPositionX()
{
	if(m_positionX.empty())
	{
		ROS_INFO("m_positionX.size(): %d",(int)m_positionX.size());
		return m_positionX;
	}
	else
	{
		return m_positionX;
	}
}

std::vector<float> ArTagFA::getPositionZ()
{
	if(m_positionZ.empty())
	{
		ROS_INFO("m_positionZ.size(): %d",(int)m_positionZ.size());
		return m_positionZ;
	}
	else
	{
		return m_positionZ;
	}
}

std::vector<float> ArTagFA::getOrientationZ()
{
	if(m_orientationZ.empty())
	{
		ROS_INFO("m_orientationZ.size(): %d",(int)m_orientationZ.size());
		return m_orientationZ;
	}
	else
	{
		return m_orientationZ;
	}
}

std::vector<float> ArTagFA::getDistance()
{
	if(m_distance.empty())
	{
		ROS_INFO("m_distance.size() = %d",(int)m_distance.size());
		return m_distance;
	}
	else
	{
		return m_distance;
	}
}

std::vector<arTag_t> ArTagFA::getArTags()
{
	if(m_arTags.empty())
	{
		ROS_WARN_NAMED("artag", "Requested empty arTags vector");
		return m_arTags;
	}
	else
	{
		return m_arTags;
	}
}
