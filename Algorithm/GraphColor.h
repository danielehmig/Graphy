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

	class GraphColor
	{
	public:
		static std::vector<struct ColorNode> colorGraph(Graphy_Graph::Graph& graph, int n);
	private:
		static bool colorHelper(std::vector<struct ColorNode>& nodes, Graphy_Graph::Graph& graph, int n, int i);
	};
}

#endif