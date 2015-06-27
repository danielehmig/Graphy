#ifndef _GRAPHCOLOR_H_
#define _GRAPHCOLOR_H_

#include "../Graph/Graph.h"

namespace Graphy_Algorithm
{
#define UNCOLORED -1

	// A simple, custom struct type to represent nodes with their colors
	struct ColorNode
	{
		Graphy_Graph::AdjListNode node;
		int color;
		int colorsTried;
		bool start;
	};

	/* ====================================================
		CLASS: GraphColor
		Perform (inefficient) graph coloring
	==================================================== */
	class GraphColor
	{
	public:

		// This function takes the given graph and attempts to color it
		// with the specified number of colors; a vector of the nodes
		// of the graph with their specified colors is returned (or an
		// empty vector if the graph cannot be colored); 
		// NOTE: The algorithm takes exponential time
		static std::vector<struct ColorNode> colorGraph(Graphy_Graph::Graph& graph, int n);
	private:
		static bool colorHelper(std::vector<struct ColorNode>& nodes, Graphy_Graph::Graph& graph, int n, int i);
	};
}

#endif