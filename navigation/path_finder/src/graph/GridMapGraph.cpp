/**
 * \file 		GridMapGraph.cpp
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2015-11-18
 * \copyright   2016, Association de Robotique de Polytech Lille All rights reserved
 * \version
 */

#include <memory>
#include "graph/GridMapGraph.h"

#include "occupancy_grid_utils.h"
namespace grid_utils = occupancy_grid_utils;

GridMapGraph::GridMapGraph() : Graph()
{

}

GridMapGraph::~GridMapGraph()
{

}

/**
 * Accesseur d'affectation de m_grid
 *
 * \param grid la gridMap à copier
 */
void GridMapGraph::setGridMap(const nav_msgs::OccupancyGrid &grid)
{
    if (m_isSearchRunning)
    {
        ROS_ERROR("Path planning in progress : Unable to modify Grid map");
        return;
    }
    m_isInit = true;
    m_grid = grid;
}

/**
 * Méthode founissant les noeuds libres accessibles à partir d'un noeud donné.
 * S'agissant d'une nav_msgs::OccupancyGrid, la fonction retourne toutes les cases
 * adjacente à la case fournie en paramètre, en connectivité 8, dont la valeur
 * est inférieure à 100. Le coût de déplacement pour passer d'une case à l'autre
 * est évalué en tenant compte de la valeur de la case.
 *
 * \param state noeud de départ
 * \param succ la liste des noeuds atteignables
 */
void GridMapGraph::getSuccessors(const std::shared_ptr<State> &state, std::list<std::shared_ptr<State>> &succ)
{
    succ.clear();
    //TODO généraliser ce code
    //On utilise les PointState pour les tests
    const std::shared_ptr<PointState> &currState = std::dynamic_pointer_cast<PointState>(state);
    const geometry_msgs::Point &p = currState->get();

    double resolution = m_grid.info.resolution;
    int cellCost = 0;
    //ROS_INFO_STREAM("Valeur de la case courante (" << p.x << "," << p.y << ") = " << grid_utils::getCellValue(m_grid, p.x, p.y));

    //TODO affiner la prise en compte de l'évaluation du cout de déplacement (stepCost)
    double stepCostModifier = 1.5;
    if ((cellCost = grid_utils::getCellValue(m_grid, p.x - resolution, p.y)) < 100)
    {
        std::shared_ptr<PointState> nextState(new PointState());
        nextState->set(p.x - resolution, p.y);
        nextState->setPrevState(state);
        nextState->setStepCost(resolution * (1.0 + double(cellCost)*stepCostModifier/100.0));
        succ.push_back(nextState);
    }
    if ((cellCost = grid_utils::getCellValue(m_grid, p.x, p.y + resolution)) < 100)
    {
        std::shared_ptr<PointState> nextState(new PointState());
        nextState->set(p.x, p.y + resolution);
        nextState->setPrevState(state);
        nextState->setStepCost(resolution * (1.0 + double(cellCost)*stepCostModifier/100.0));
        succ.push_back(nextState);
    }
    if ((cellCost = grid_utils::getCellValue(m_grid, p.x + resolution, p.y)) < 100)
    {
        std::shared_ptr<PointState> nextState(new PointState());
        nextState->set(p.x + resolution, p.y);
        nextState->setPrevState(state);
        nextState->setStepCost(resolution * (1.0 + double(cellCost)*stepCostModifier/100.0));
        succ.push_back(nextState);
    }
    if ((cellCost = grid_utils::getCellValue(m_grid, p.x, p.y - resolution)) < 100)
    {
        std::shared_ptr<PointState> nextState(new PointState());
        nextState->set(p.x, p.y - resolution);
        nextState->setPrevState(state);
        nextState->setStepCost(resolution * (1.0 + double(cellCost)*stepCostModifier/100.0));
        succ.push_back(nextState);
    }
    static double sqrt_2 = sqrt(2.0);
    if ((cellCost = grid_utils::getCellValue(m_grid, p.x - resolution, p.y - resolution)) < 100)
    {
        std::shared_ptr<PointState> nextState(new PointState());
        nextState->set(p.x - resolution, p.y - resolution);
        nextState->setPrevState(state);
        nextState->setStepCost(resolution*sqrt_2 * (1.0 + double(cellCost)*stepCostModifier/100.0));
        succ.push_back(nextState);
    }
    if ((cellCost = grid_utils::getCellValue(m_grid, p.x - resolution, p.y + resolution)) < 100)
    {
        std::shared_ptr<PointState> nextState(new PointState());
        nextState->set(p.x - resolution, p.y + resolution);
        nextState->setPrevState(state);
        nextState->setStepCost(resolution*sqrt_2 * (1.0 + double(cellCost)*stepCostModifier/100.0));
        succ.push_back(nextState);
    }
    if ((cellCost = grid_utils::getCellValue(m_grid, p.x + resolution, p.y + resolution)) < 100)
    {
        std::shared_ptr<PointState> nextState(new PointState());
        nextState->set(p.x + resolution, p.y + resolution);
        nextState->setPrevState(state);
        nextState->setStepCost(resolution*sqrt_2 * (1.0 + double(cellCost)*stepCostModifier/100.0));
        succ.push_back(nextState);
    }
    if ((cellCost = grid_utils::getCellValue(m_grid, p.x + resolution, p.y - resolution)) < 100)
    {
        std::shared_ptr<PointState> nextState(new PointState());
        nextState->set(p.x + resolution, p.y - resolution);
        nextState->setPrevState(state);
        nextState->setStepCost(resolution*sqrt_2 * (1.0 + double(cellCost)*stepCostModifier/100.0));
        succ.push_back(nextState);
    }
}

/**
 * Méthode founissant les noeuds à partir desquels on peut accéder à un noeud donné
 * Cette méthode est identique à getSuccessors() dans le cas d'une gridMap (graph non orienté)
 *
 * \param state noeud d'arrivée
 * \param pred la liste des noeuds précedents
 */
void GridMapGraph::getPredecessors(const std::shared_ptr<State> &state, std::list<std::shared_ptr<State>> &pred)
{
    getSuccessors(state, pred);
}

/**
 * Méthode qui retourne le noeud le plus proche dans le graph pour un point fourni
 *
 * \param state noeud fourni
 * \param closestState noeud le plus proche
 */
void GridMapGraph::getClosestNode(const std::shared_ptr<State> &state, std::shared_ptr<State> &closestState) const
{
    std::shared_ptr<PointState> newState(new PointState());
    const std::shared_ptr<PointState> &pState = std::dynamic_pointer_cast<PointState>(state);

    double resolution = m_grid.info.resolution;
    double x = round(pState->get().x / resolution) * resolution;
    double y = round(pState->get().y / resolution) * resolution;
    newState->set(x, y);
    closestState = newState;
}
