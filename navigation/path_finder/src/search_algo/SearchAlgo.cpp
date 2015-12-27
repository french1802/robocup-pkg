/**
 * \file 		SearchAlgo.cpp
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2015-11-18
 * \copyright	PyroTeam, Polytech-Lille
 * \license
 * \version
 */

#include "search_algo/SearchAlgo.h"
#include "graph/Graph.h"

SearchAlgo::SearchAlgo(const std::shared_ptr<Graph> &graph, bool reverse):m_graph(graph), m_reverse(reverse)
{

}

SearchAlgo::~SearchAlgo()
{

}