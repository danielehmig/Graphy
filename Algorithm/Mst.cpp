#include "Mst.h"

namespace Graphy_Algorithm
{
	/* ====================================================
		mst(Graph)
	==================================================== */
	Graphy_Graph::Graph Mst::mst(Graphy_Graph::Graph& orig)
	{
		// Create the initial list of edges (of our custom type)
		std::priority_queue<struct edge, std::vector<struct edge>, Compare> edges;

		// Create our return value graph
		Graphy_Graph::Graph ret;

		// Go through each edge in our graph and add it to our heap
		std::vector<Graphy_Graph::AdjListNode> nodes = orig.getAllNodes();
		for (std::vector<Graphy_Graph::AdjListNode>::iterator it = nodes.begin(); 
				it != nodes.end(); it++)
		{
			ret.addNode(*it);

			Graphy_Graph::AdjList ce = orig.connectedEdges(*it);
			std::forward_list<int> costs = ce.getCostList();
			std::forward_list<int>::iterator ci = costs.begin();
			for (Graphy_Graph::AdjList::iterator it2 = ce.begin(); it2 != ce.end(); it2++)
			{
				struct edge e;
				e.src = *it;
				e.dst = *it2;
				e.cost = *ci;
				ci++;

				edges.push(e);
			}
		}

		// Create the forests where, at first, each node is its own forest
		std::vector<std::unordered_set<Graphy_Graph::AdjListNode>> forests;
		for (int i = 0; i < orig.numNodes(); ++i)
		{
			std::unordered_set<Graphy_Graph::AdjListNode> newSet;
			newSet.insert(orig.getNodeAtIndex(i));
			forests.push_back(newSet);
		}

		// Now, start the mst algorithm

		int count = 0;
		while (!edges.empty())
		{

			struct edge min = edges.top();
			edges.pop();

			int srcIndex = min.src.getIndex();
			int dstIndex = min.dst.getIndex();

			if (!setEqual(forests[srcIndex], forests[dstIndex]))
			{
				ret.addEdge(min.src, min.dst, min.cost);

				
				unionSets(forests[srcIndex], forests[dstIndex], forests);
				
				for (std::unordered_set<Graphy_Graph::AdjListNode>::iterator it = forests[srcIndex].begin();
					it != forests[srcIndex].end(); it++)
				{
					unionSets(forests[it->getIndex()], forests[dstIndex], forests);
				}

				for (std::unordered_set<Graphy_Graph::AdjListNode>::iterator it = forests[dstIndex].begin();
					it != forests[dstIndex].end(); it++)
				{
					unionSets(forests[it->getIndex()], forests[srcIndex], forests);
				}
				
			}
		}

		// At this point, we (allegedly) have our mst; return it to the user
		return ret;
	}

	/* ====================================================
		unionSets(unordered_set<AdjListNode>,
				  unordered_set<AdjListNode>,
				  vector<unordered_set<AdjListNode>>)
	==================================================== */
	void Mst::unionSets(std::unordered_set<Graphy_Graph::AdjListNode>& a,
		std::unordered_set<Graphy_Graph::AdjListNode>& b,
		std::vector<std::unordered_set<Graphy_Graph::AdjListNode>>& forests)
	{

		for (std::unordered_set<Graphy_Graph::AdjListNode>::iterator it = a.begin();
			it != a.end(); it++)
		{
			b.insert(*it);
		}

		for (std::unordered_set<Graphy_Graph::AdjListNode>::iterator it = b.begin();
			it != b.end(); it++)
		{
			a.insert(*it);
		}
	}

	/* ====================================================
		setEqual(unordered_set<AdjListNode>,
				 unordered_set<AdjListNode>)
	==================================================== */
	bool Mst::setEqual(std::unordered_set<Graphy_Graph::AdjListNode> a, 
					std::unordered_set<Graphy_Graph::AdjListNode> b)
	{
		if (a.size() != b.size())
		{
			return false;
		}
		else
		{
			for (std::unordered_set<Graphy_Graph::AdjListNode>::iterator it = a.begin(); 
					it != a.end(); it++)
			{
				if (b.find(*it) == b.end())
				{
					return false;
				}
			}

			// TODO: Probably don't need this second for-loop
			for (std::unordered_set<Graphy_Graph::AdjListNode>::iterator it = b.begin();
					it != b.end(); it++)
			{
				if (a.find(*it) == a.end())
				{
					return false;
				}
			}
		}
		return true;
	}

	/* ====================================================
		eraseNode(vector<AdjListNode>, AdjListNode)
	==================================================== */
	void Mst::eraseNode(std::vector<Graphy_Graph::AdjListNode>& nodes, Graphy_Graph::AdjListNode& node)
	{
		for (std::vector<Graphy_Graph::AdjListNode>::iterator it = nodes.begin();
			it != nodes.end(); it++)
		{
			if (*it == node)
			{
				nodes.erase(it);
				break;
			}
		}
	}
}