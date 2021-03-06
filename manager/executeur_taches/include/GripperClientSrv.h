/**
 * \file        GripperClientSrv.h
 * \class       GripperClientSrv
 * \brief       classe client pour la pince
 * \author      Hage Chehade Sandra (sandra.hage-chehade@polytech-lille.net)
 * \date        2015-10-10
 * \copyright   2016, Association de Robotique de Polytech Lille All rights reserved
 */

#ifndef GRIPPERCLIENTSRV_H
#define GRIPPERCLIENTSRV_H


#include "ros/ros.h"
#include "manager_msg/SetGripper.h"
#include <cstdlib>

class GripperClientSrv 
{
	public:
		/* Constructeur */
		GripperClientSrv();

		/* Déstructeur */
		virtual  ~GripperClientSrv();

		/* Méthodes */
		bool gripper_uppdate(bool new_state);
};
#endif