#ifndef _MST_H_
#define _MST_H_
#include "../Graph/Graph.h"
#include <queue>
#include <unordered_set>

namespace Graphy_Algorithm
{

	// Define a custom edge type specifically for MST to obtain cost more easily
	struct edge
	{
		Graphy_Graph::AdjListNode src;
		Graphy_Graph::AdjListNode dst;
		int cost;
	};

	/* ====================================================
		CLASS: Mst
		Determine the minimum spanning tree of a graph
	==================================================== */
	static class Mst
	{
	public:

		// This function takes a Graphy Graph as input and returns a graph
		// that represents the minimum spanning tree for the given graph (if any)
		// If there is no MST for the given graph, a forest of non-contiguous trees are returned.
		// NOTE: This function has no side effects.
		static Graphy_Graph::Graph mst(Graphy_Graph::Graph& orig);

	private:
		static void eraseNode(std::vector<Graphy_Graph::AdjListNode>& nodes, Graphy_Graph::AdjListNode& node);
		static bool setEqual(std::unordered_set<Graphy_Graph::AdjListNode> a, std::unordered_set<Graphy_Graph::AdjListNode> b);
		static void unionSets(std::unordered_set<Graphy_Graph::AdjListNode>& a, std::unordered_set<Graphy_Graph::AdjListNode>& b,
			std::vector<std::unordered_set<Graphy_Graph::AdjListNode>>& forests);
	};

	/* ====================================================
		CLASS: Compare
		Custom comparator to compare two struct edges
	==================================================== */
	class Compare
	{
	public:
		bool operator() (struct edge a, struct edge b)
		{
			if (a.cost <= b.cost)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	};
}

#endif