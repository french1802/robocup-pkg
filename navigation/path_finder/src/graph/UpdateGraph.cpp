/**
 * \file 		UpdateGraph.cpp
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2015-11-19
 * \copyright   2016, Association de Robotique de Polytech Lille All rights reserved
 * \version
 */

#include "graph/UpdateGraph.h"

UpdateGraph::UpdateGraph(const std::string &topicName, const std::shared_ptr<Graph> &graph):m_graph(graph)
{

}

UpdateGraph::~UpdateGraph()
{

}
