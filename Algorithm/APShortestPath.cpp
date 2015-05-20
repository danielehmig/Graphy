#include "APShortestPath.h"
#include "Dijkstra.h"

namespace Graphy_Algorithm
{
	std::vector<std::vector<std::vector<Graphy_Graph::AdjListNode>>> 
		APShortestPath::apShortestPath(Graphy_Graph::Graph& graph)
	{
		// In order to find the shortest path between every pair of nodes
		// in the graph, we can run Dijkstra's algorithm for every possible
		// pair of nodes. However, we can use some dynamic programming to 
		// reduce the number of times that we need to run Dijkstra.

		// Create and initialize the 2D matrix of paths
		int numNodes = graph.numNodes();
		std::vector<std::vector<std::vector<Graphy_Graph::AdjListNode>>> retVal(numNodes);

		// The object that we will run dijkstra on
		Dijkstra dij;

		std::vector<Graphy_Graph::AdjListNode> ** matrix = 
			new std::vector<Graphy_Graph::AdjListNode> * [numNodes];

		for (int i = 0; i < numNodes; ++i)
		{
			matrix[i] = new std::vector<Graphy_Graph::AdjListNode>[numNodes];
		}

		// Now, we're ready to fill in the matrix
		// If a vector is empty, we haven't computed the path or there is no path
		// (currently, there is no way to disambiguate the two cases)
		for (int i = 0; i < numNodes; ++i)
		{
			for (int j = 0; j < numNodes; ++j)
			{
				if (matrix[i][j].empty())
				{
					Graphy_Graph::AdjListNode src = graph.getNodeAtIndex(i);
					Graphy_Graph::AdjListNode dst = graph.getNodeAtIndex(j);
					std::vector<Graphy_Graph::AdjListNode> path = dij.dijkstra(graph, src, dst);
					matrix[i][j] = path;

					if (!path.empty())
					{
						path.pop_back();

						// We computed all the sub-paths, so we can fill those in
						while (path.size() > 1)
						{
							int srcIndex = path.back().getIndex();
							matrix[srcIndex][j] = path;
							path.pop_back();
						}
					}
					
				}
			}
		}

		// Now, fill in the return value
		for (int i = 0; i < numNodes; ++i)
		{
			retVal.push_back(std::vector<std::vector<Graphy_Graph::AdjListNode>>());
		}

		// Fill in column-wise
		for (int j = 0; j < numNodes; ++j)
		{
			for (int i = 0; i < numNodes; ++i)
			{
				retVal[j].push_back(matrix[i][j]);
			}
		}

		// Delete the heap-allocated memory
		/*for (int i = 0; i < numNodes; ++i)
		{
			delete matrix[i];
		}*/

		// We're done here
		return retVal;
	}
}