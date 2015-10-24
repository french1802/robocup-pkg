/**
 * \file 		robot.h
 * \class		Robot
 * \brief		classe représentant l'état d'un robot
 * \author		Smagghe Cyril (cyril.smagghe@polytech-lille.net)
 * \date		2015-04-01
 * \copyright	PyroTeam, Polytech-Lille
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "manager_msg/activity.h"

class Robot{
 
public :
 
	Robot(){m_busy=true; m_machine=manager_msg::activity::NONE; m_nbOrder=0;}
 
	bool getBusy(){return m_busy;}
	void setBusy(bool busy){m_busy = busy;}
	int getMachine(){return m_machine;}
	void setMachine(int machine){m_machine=machine;}
	int getNbOrder(){return m_nbOrder;}
	void setNbOrder(int ordre){m_nbOrder=ordre;}
  
private :
  
	bool m_busy; //indique si le robot est occupe ou non
	int m_machine;
	int m_nbOrder;

};

#endif