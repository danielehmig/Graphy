#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "../Graph/Graph.h"
#include <climits>

namespace Graphy_Algorithm
{

#define UNDEFINED_PREV -1
#define INFINITE_DIST INT_MAX
	class Dijkstra
	{
	public:

		// This function takes a Graph, a start node, and a destination node,
		// then finds the shortest path (if any) between the two. The return value is
		// an ordered vector of nodes that specifies the path between the two nodes,
		// where the node in the 0th position in the vector is the destination and the node
		// in the (size-1)th position in the vector is the start node.
		// NOTE: The path ordering in the vector is REVERSED.
		std::vector<Graphy_Graph::AdjListNode> dijkstra(Graphy_Graph::Graph& graph, 
														Graphy_Graph::AdjListNode& start, 
														Graphy_Graph::AdjListNode& dst);
	};
}

#endif