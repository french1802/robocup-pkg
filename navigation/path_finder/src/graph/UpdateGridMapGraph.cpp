/**
 * \file 		UpdateGridMapGraph.cpp
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2015-11-19
 * \copyright   2016, Association de Robotique de Polytech Lille All rights reserved
 * \version
 */

#include "graph/UpdateGridMapGraph.h"

UpdateGridMapGraph::UpdateGridMapGraph(const std::string &topicName, const std::shared_ptr<Graph> &graph):UpdateGraph(topicName, graph)
{
    m_graph_sub = m_nh.subscribe(topicName, 1000, &UpdateGridMapGraph::mapCallback, this);

}

UpdateGridMapGraph::~UpdateGridMapGraph()
{

}

/**
 * Méthode de callback ROS sur un topic fournissant une gridMap
 *
 * \param grid la gridMap reçue
 */
void UpdateGridMapGraph::mapCallback(const nav_msgs::OccupancyGrid &grid)
{
    if (m_graph->isSearchRunning())
    {
        return;
    }
    std::shared_ptr<GridMapGraph> gridMapGraph = std::static_pointer_cast<GridMapGraph>(m_graph);

    gridMapGraph->setGridMap(grid);

}
