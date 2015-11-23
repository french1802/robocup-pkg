/**
 * \file 		AStarSearch.cpp
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2015-11-19
 * \copyright	PyroTeam, Polytech-Lille
 * \license
 * \version
 */

#include <iostream>
#include "ros/ros.h"
#include "search_algo/AStarSearch.h"
#include "search_algo/AStarState.h"

AStarSearch::AStarSearch(const std::shared_ptr<Graph> &graph) : SearchAlgo(graph), m_openList(StateComparison(true))
{

}

AStarSearch::~AStarSearch()
{

}

/**
 * Méthode de recherche implémentant l'algorithme Astar.
 *
 * \param startState noeud de départ
 * \param endState noeud d'arrivée
 * \param path le chemin généré
 */
 //TODO utiliser la classe Path plutot qu'une std::list<std::shared_ptr<State>>
void AStarSearch::search(std::shared_ptr<State> &startState, std::shared_ptr<State> &endState, std::list<std::shared_ptr<State>> &path)
{
    ROS_INFO_STREAM("PahtFinder : Recherche un chemin : \n Depart \n" << *startState << "\n Arrivee \n" << *endState);
    m_openList.clear();
    m_closedSet.clear();
    m_openList.push(startState);
    while (!m_openList.empty())
    {
        //on traite le noeud ayant le cout de chemin le plus faible dans m_openList
        std::shared_ptr<State> currentState = m_openList.top();
        //ROS_INFO_STREAM("Traitement d'un noeud : \n" << *currentState);
        std::shared_ptr<AStarState> currAStarState = std::static_pointer_cast<AStarState>(currentState);
        m_openList.pop();

        //si ce noeud est le noeud final alors on a terminé
        if (*currentState == *endState)
        {
            ROS_INFO_STREAM("Chemin trouvé");
            //on peut reconstruire le chemin ...
            path.clear();
            std::shared_ptr<State> temp = currentState;
            while (temp != nullptr)
            {
                path.push_front(temp);
                temp = temp->getPrevState();
            }
            //... et quitter la fonction
            return;
        }

        //si le noeud se trouve déjà dans m_closedSet alors on l'a déjà traité auparavant
        if(m_closedSet.find(currentState) != m_closedSet.end())
        {
            //ROS_INFO_STREAM("Noeud courant déjà dans ClosedSet");
            //on ne fait rien et on passe au noeud suivant
            continue;
        }
        else
        {
            //sinon, on ajoute le noeu à m_closedSet
            //ROS_INFO_STREAM("Ajout noeud a ClosedSet");
            m_closedSet.insert(currentState);

            //ensuite on récupère tous les noeuds succésseur du noeud courant
            std::list<std::shared_ptr<State>> succ;
            m_graph->getSuccessors(currentState, succ);
            //ROS_INFO_STREAM("Nombre de noeud succ = " << succ.size());

            for (auto &s : succ)
            {
                std::shared_ptr<AStarState> sStar = std::static_pointer_cast<AStarState>(s);

                //Pour chaque noeud succésseur on calcul :
                // - le coût de deplacement depuis le noeud de départ,
                double gCost = currAStarState->getGCost()+s->getStepCost();

                // - une évaluation du coût du chemin restant à parcourir
                //   pour atteindre le noeud de destination, via une heuristique,
                //test technique tie breaking h = h*(1.0+p) (avec p un poucentage faible)
                //voir http://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html
                double hCost = m_graph->evaluateHeuristic(*s, *endState) * (1.0 + 1.0/10000.0);

                // - une évaluation du coût global du chemin passant par ce noeud.
                double fCost = gCost + hCost;
                sStar->setGCost(gCost);
                sStar->setCost(fCost);

                //enfin on ajoute ce noeud à m_openList
                //ROS_INFO_STREAM("Ajout successor à OpenList : \n" << *s);
                m_openList.push(s);
            }

        }
    }
    //pas de chemin trouvé
}
