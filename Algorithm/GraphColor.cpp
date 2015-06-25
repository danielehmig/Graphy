#include "GraphColor.h"

namespace Graphy_Algorithm
{
	std::vector<struct ColorNode> GraphColor::colorGraph(Graphy_Graph::Graph& graph, int n)
	{
		std::vector<struct ColorNode> nodes(graph.numNodes());
		std::vector<Graphy_Graph::AdjListNode> theRealNodes = graph.getAllNodes();
		for (std::vector<Graphy_Graph::AdjListNode>::iterator it = theRealNodes.begin();
				it != theRealNodes.end(); it++)
		{
			struct ColorNode c;
			c.node = *it;
			c.color = UNCOLORED;
			c.colorsTried = 0;
			if (it == theRealNodes.begin())
			{
				c.start = true;
			}
			else
			{
				c.start = false;
			}
			nodes.push_back(c);
		}

		// colorHelper() will actually be doing the bulk of the work
		if (!colorHelper(nodes, graph, n, 0))
		{
			nodes.clear();
		}

		return nodes;
	}

	bool GraphColor::colorHelper(std::vector<struct ColorNode>& nodes, Graphy_Graph::Graph& graph, int n, int i)
	{
		struct ColorNode * currNode = &nodes[i];

		currNode->colorsTried = 0;
		// NOTE: Condition here might be off by one
		while (currNode->colorsTried < n)
		{
			currNode->color = currNode->colorsTried;

			// Now, check the neighbors to see if this color works
			bool * colors = new bool[n];
			Graphy_Graph::AdjList nebs = graph.connectedEdges(currNode->node);
			for (Graphy_Graph::AdjList::iterator it = nebs.begin(); it != nebs.end(); it++)
			{
				if (nodes[it->getIndex()].color != UNCOLORED)
				{
					colors[nodes[it->getIndex()].color] = true;
				}
			}

			if (colors[currNode->color])
			{
				currNode->colorsTried++;
			}
			else
			{
				// Now, recurse on each uncolored neighbor
				Graphy_Graph::AdjList::iterator it = nebs.begin();
				for (; it != nebs.end(); it++)
				{
					if (nodes[it->getIndex()].colorsTried == 0)
					{
						if (!colorHelper(nodes, graph, n, it->getIndex()))
						{
							currNode->colorsTried++;
							break;
						}
					}
				}

				if (it == nebs.end())
				{
					// We successfully colored the neigbors, so we can exit the loop
					break;
				}
			}

			delete[] colors;
		}

		if (currNode->colorsTried == n)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}