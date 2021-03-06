/**
 * \file 		work.h
 * \brief		fonctions utiles concernant la production totale des produits
 * \author		Smagghe Cyril (cyril.smagghe@polytech-lille.net)
 * \date		2015-04-01
 * \copyright   2016, Association de Robotique de Polytech Lille All rights reserved
 */

#ifndef WORK_H
#define WORK_H

#include "task.h"

#include "comm_msg/Order.h"

/**
 *	\brief		vérifie si un ordre passé en paramètre est déjà pris en compte 
 *				par la structure de travail
 *	\return		true si ordre déjà pris en compte sinon false
 */
bool alreadyInWork(std::list<std::list<Task> > work,  comm_msg::Order order);

/**
 *	\brief		détermine la liste de tâches ayant le plus grand ratio
 *	\return		un itérateur sur la liste ayant le plus grand ratio
 */
std::list<std::list<Task> >::iterator maxRatio(std::list<std::list<Task> > &work);

/**
 *	\brief		vérifie qu'il y ait au moins une taĉhe avec un ratio strictement positif
 *	\return		true s'il y a un ratio strictement positif sinon false
 */
bool positiveRatio(std::list<std::list<Task> > work);

/**
 *	\brief		rajoute un ordre de la RefBox dans la structure de travail
 */
void addInWork(std::list<std::list<Task> > &work, std::vector<comm_msg::Order> tabOrders, int (&availableCap)[2], std::vector<bool> &ordersInProcess);

/**
 *	\brief		calcule le ratio de chaque premier élément de chaque liste de tâches
 */
void ratioCalculus(std::list<std::list<Task> > &work,double time,int robot,bool take[3]);

/**
 *	\brief		affiche les infos générales sur la structure de travail
 */
void getInfoWork(std::list<std::list<Task> > work);

/**
 *	\brief		supprime les tâches réalisées
 */
void cleanWork(std::list<std::list<Task> > &work,std::list<std::list<Task> >::iterator &it, double time);

/**
 *	\brief		effectue des traitements distincts pour certaines tâches
 */
void particularTasksInWork(std::list<std::list<Task> > ::iterator &it, int (&availableCap)[2], int &storage, double time);

/**
 *	\brief		vérifie les tâches terminées
 */
void finishedTasks(std::list<std::list<Task> > &work, double time);

void addNewTasksList(std::list<std::list<Task> > &work, comm_msg::Order order, int availableCap);

void addAccordingToCap(std::list<std::list<Task> > &work, comm_msg::Order order,int (&availableCap)[2]);

#endif
