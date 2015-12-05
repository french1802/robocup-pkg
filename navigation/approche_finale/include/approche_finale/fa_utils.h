/**
 * \file 			fa_utils.h
 * \brief			ensemble de fonctions nécessaires pour l'approche finale
 * \author			Smagghe Cyril (cyril.smagghe@polytech-lille.net)
 * \date			2015-04-20
 * \copyright		PyroTeam, Polytech-Lille
 */

#ifndef FA_UTILS_H
#define FA_UTILS_H

#include <ros/ros.h>
#include <vector>
#include "Point.h"
#include "approche_finale_msg/plotDataFA.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Pose2D.h"


geometry_msgs::Point orthoProjection(Point p, geometry_msgs::Pose2D p2d);
/**
 *  \brief		Calcule la distance en m entre deux points
 *  \return		distance en m entre deux points
 */ 
float distance2points(Point a, Point b);

/**
 *  \brief		Fait une moyenne
 *  \return		la valeur moyenne de l'ensemble des flottants passes en parametres
 */ 
float moy(std::list<float> positionY);

/**
 *  \brief		permet d asservir en angle
 *  \return		etat d avancement de l asservissement
 */ 
int asservissementAngle(approche_finale_msg::plotDataFA &plotData,ros::Publisher pubMvt,float moyGradient);

/**
 *  \brief		permet d asservir en y (repere laser)
 *  \return		etat d avancement de l asservissement
 */ 
int asservissementPositionY(approche_finale_msg::plotDataFA &plotData,ros::Publisher pubMvt, float goal, float moyPos, float yLeft, float yRight);

/**
 *  \brief		permet d asservir en x (repere laser)
 *  \return		etat d avancement de l asservissement
 */ 
int asservissementPositionX(approche_finale_msg::plotDataFA &plotData,ros::Publisher pubMvt, float distance, float goal);


#endif