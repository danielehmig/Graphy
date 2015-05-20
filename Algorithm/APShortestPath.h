#ifndef _APSHORTESTPATH_H_
#define _APSHORTESTPATH_H_

#include "../Graph/Graph.h"

namespace Graphy_Algorithm
{
	static class APShortestPath
	{
	public:
		// This static function returns a n x n matrix of paths, where n is the number
		// of nodes in the graph. The matrix is represented by 2D vector data structure,
		// where each position (i, j) in the 2D matrix is the path from node i to node j.
		// The path will be empty if there is no path (i.e., if no path actually exists
		// or there was an error for some reason).
		static std::vector<std::vector<std::vector<Graphy_Graph::AdjListNode>>> apShortestPath(Graphy_Graph::Graph& graph);
	};
}

#endif