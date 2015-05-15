#include "Dijkstra.h"

namespace Graphy_Algorithm
{
	/* ====================================================
		dijkstra(Graph, AdjListNode, AdjListNode)
	==================================================== */
	std::vector<Graphy_Graph::AdjListNode> Dijkstra::dijkstra(Graphy_Graph::Graph& graph,
		Graphy_Graph::AdjListNode& start,
		Graphy_Graph::AdjListNode& dst)
	{

		// Check that the nodes are actually in the graph
		if (!graph.nodeExists(start) || !graph.nodeExists(dst))
		{
			// Return an empty vector because there is no path
			return std::vector<Graphy_Graph::AdjListNode>();
		}

		// Special case if the start and dst nodes are the same
		if (start == dst)
		{
			// Return an empty vector because there is no path
			return std::vector<Graphy_Graph::AdjListNode>();
		}


		std::vector<int> dist;
		std::vector<int> prev;
		std::vector<Graphy_Graph::AdjListNode> unvisited = graph.getAllNodes();

		// Initialize the distances to infinity and each prev to undefined
		for (int i = 0; i < graph.numNodes(); ++i)
		{
			dist.push_back(INFINITE_DIST);
			prev.push_back(UNDEFINED_PREV);
		}

		// There is no cost to get from the start node to itself
		// (will cause the start node to be the first one removed)
		dist[start.getIndex()] = 0;

		while (!unvisited.empty())
		{
			int min = dist[unvisited[0].getIndex()];
			int minIndex = unvisited[0].getIndex();
			Graphy_Graph::AdjListNode minNode = unvisited[0];
			std::vector<Graphy_Graph::AdjListNode>::iterator minIt = unvisited.begin();

			// Find the minimum value in the array of distances
			for (std::vector<Graphy_Graph::AdjListNode>::iterator it = unvisited.begin();
				it != unvisited.end(); it++)
			{
				int index = it->getIndex();
				if (dist[index] < min)
				{
					min = dist[index];
					minIndex = index;
					minNode = *it;
					minIt = it;
				}
			}

			// If the minimum is infinity, there is no path
			/*if (min == INFINITE_DIST)
			{
				return std::vector<Graphy_Graph::AdjListNode>();
			}*/

			// Remove the minimum so we don't consider it again
			unvisited.erase(minIt);

			Graphy_Graph::AdjList neighbors = graph.connectedEdges(minNode);
			std::forward_list<int> costs = neighbors.getCostList();
			std::forward_list<int>::iterator costIt = costs.begin();

			// For each (unvisited) neighbor of the minimum node, update the costs
			for (Graphy_Graph::AdjList::iterator it = neighbors.begin();
				it != neighbors.end(); it++)
			{
				// TODO: Find a more efficient way to determine
				// if the neighbor is unvisited
				std::vector<Graphy_Graph::AdjListNode>::const_iterator iter = unvisited.begin();
				for (; iter != unvisited.end(); iter++)
				{
					if (*iter == *it)
					{
						break;
					}
				}

				if (iter != unvisited.end())
				{
					int alt = min + (*costIt);
					if (alt <= dist[it->getIndex()])
					{
						dist[it->getIndex()] = alt;
						prev[it->getIndex()] = minIndex;
					}
				}
				costIt++;
			}
		}

		std::vector<Graphy_Graph::AdjListNode> ret;
		int u = prev[dst.getIndex()];

		if (u == UNDEFINED_PREV)
		{
			// There is no path
			return std::vector<Graphy_Graph::AdjListNode>();
		}
		
		// Remember to put the dst node on the path
		ret.push_back(dst);

		// Push the shortest path onto the vector to return
		while (prev[u] != UNDEFINED_PREV)
		{
			ret.push_back(graph.getNodeAtIndex(u));
			u = prev[u];

			// If we're looping indefinetely, then there is no path
			if (ret.size() > graph.numNodes())
			{
				return std::vector<Graphy_Graph::AdjListNode>();
			}
		}

		// The loop does not consider the start node because
		// prev[starting index] is undefined
		ret.push_back(start);

		return ret;
	}
}