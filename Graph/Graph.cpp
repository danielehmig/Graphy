#include "Graph.h"

namespace Graphy_Graph
{

	/* ==================================================== 
		Graph()
	==================================================== */
	Graph::Graph()
	{
		mNumEdges = 0;
		mNumNodes = 0;
		mDirected = false;
	}

	/* ====================================================
		Graph(int, bool)
	==================================================== */
	Graph::Graph(int capacity, bool directed)
	{
		mNumEdges = 0;
		mNumNodes = 0;
		mDirected = true;

		// Increase the vector's capacity to hold at least <capacity> elements
		mGraph.reserve(capacity);
	}

	/* ====================================================
		Graph(Graph)
	==================================================== */
	Graph::Graph(const Graph& other)
	{
		mNumEdges = other.mNumEdges;
		mNumNodes = other.mNumNodes;
		mDirected = other.mDirected;

		for (std::map<std::string, int>::const_iterator it = other.mLabelMap.begin();
				it != other.mLabelMap.end(); it++)
		{
			mLabelMap.insert(std::pair<std::string, int>(it->first, it->second));
		}

		for (std::vector<AdjList>::const_iterator it = other.mGraph.begin();
				it != other.mGraph.end(); it++)
		{
			mGraph.push_back(*it);
		}
	}

	/* ====================================================
		addNode(AdjListNode)
	==================================================== */
	void Graph::addNode(const AdjListNode& node)
	{
		addNode(node.getLabel());
	}

	/* ====================================================
		addNode(string)
	==================================================== */
	void Graph::addNode(const std::string& label)
	{
		int nextIndex = mGraph.size();

		std::pair<std::map<std::string, int>::iterator, bool> ret;
		ret = mLabelMap.insert(std::pair<std::string, int>(label, nextIndex));

		// Only insert if the node isn't already in the graph
		if (ret.second)
		{
			AdjListNode newNode(label, nextIndex);
			AdjList newList(newNode);
			mGraph.push_back(newList);
			mNumNodes++;
		}
	}

	/* ====================================================
		removeNode(AdjListNode)
	==================================================== */
	void Graph::removeNode(const AdjListNode& node)
	{
		removeNode(node.getLabel());
	}

	/* ====================================================
		removeNode(string)
	==================================================== */
	void Graph::removeNode(const std::string& label)
	{
		try
		{
			int index = mLabelMap.at(label);
			AdjListNode node = mGraph[index].getNode();

			// If the graph is undirected, we can save some computations by
			// just doing bidirectional removals
			if (!mDirected)
			{
				while (!mGraph[index].empty())
				{
					AdjListNode temp = mGraph[index].front();
					mGraph[index].removeNode(temp);
					int tempIndex = mLabelMap.at(temp.getLabel());
					mGraph[tempIndex].removeNode(node);
					mNumEdges--;
				}
			}
			else
			{
				// Otherwise, we don't know what directed edges end
				// at the node we are trying to remove
				for (std::vector<AdjList>::iterator it = mGraph.begin(); it != mGraph.end(); it++)
				{
					// Won't do anything if node isn't actually in the adjacency list
					int n1 = it->numEdges();
					it->removeNode(node);
					int n2 = it->numEdges();

					mNumEdges -= (n1 - n2);
				}

				std::vector<AdjList>::iterator remover = mGraph.begin();
				remover += index;
				// Destroy the node's adjacency list
				mNumEdges -= remover->numEdges();
				mGraph.erase(remover);
			}
			mNumNodes--;
		}
		catch (std::out_of_range e)
		{
		}
	}

	/* ====================================================
		addEdge(AdjListNode, AdjListNode)
	==================================================== */
	void Graph::addEdge(const AdjListNode& src, const AdjListNode& dst)
	{
		addEdge(src.getLabel(), dst.getLabel());
	}

	/* ====================================================
		addEdge(string, string)
	==================================================== */
	void Graph::addEdge(const std::string& src, const std::string& dst)
	{
		try
		{
			int srcIndex = mLabelMap.at(src);
			int dstIndex = mLabelMap.at(dst);

			int n1 = mGraph[srcIndex].numEdges();
			mGraph[srcIndex].addNode(mGraph[dstIndex].getNode());
			int n2 = mGraph[srcIndex].numEdges();

			mNumEdges += (n2 - n1);

			if (!mDirected)
			{
				int n1 = mGraph[dstIndex].numEdges();
				mGraph[dstIndex].addNode(mGraph[srcIndex].getNode());
				int n2 = mGraph[dstIndex].numEdges();
				mNumEdges += (n2 - n1);
			}
		}
		catch (std::out_of_range e)
		{
		}
	}

	/* ====================================================
		removeEdge(AdjListNode, AdjListNode)
	==================================================== */
	void Graph::removeEdge(const AdjListNode& src, const AdjListNode& dst)
	{
		removeEdge(src.getLabel(), dst.getLabel());
	}

	/* ====================================================
		removeEdge(string, string)
	==================================================== */
	void Graph::removeEdge(const std::string& src, const std::string& dst)
	{
		try
		{
			int srcIndex = mLabelMap.at(src);
			int dstIndex = mLabelMap.at(dst);

			int n1 = mGraph[srcIndex].numEdges();
			mGraph[srcIndex].removeNode(mGraph[dstIndex].getNode());
			int n2 = mGraph[srcIndex].numEdges();

			mNumEdges -= (n1 - n2);

			if (!mDirected)
			{
				n1 = mGraph[dstIndex].numEdges();
				mGraph[dstIndex].removeNode(mGraph[srcIndex].getNode());
				n2 = mGraph[dstIndex].numEdges();

				mNumEdges -= (n1 - n2);
			}
		}
		catch (std::out_of_range e)
		{
		}
	}

	/* ====================================================
		edgeExists(AdjListNode, AdjListNode)
	==================================================== */
	bool Graph::edgeExists(const AdjListNode& src, const AdjListNode& dst) const
	{
		return edgeExists(src.getLabel(), dst.getLabel());
	}

	/* ====================================================
		edgeExists(string, string)
	==================================================== */
	bool Graph::edgeExists(const std::string& src, const std::string& dst) const
	{
		try
		{
			int index = mLabelMap.at(src);
			int index2 = mLabelMap.at(dst);
			return mGraph[index].exists(mGraph[index2].getNode());
		}
		catch (std::out_of_range e)
		{
			// One of the at() calls failed
			return false;
		}
	}

	/* ====================================================
		nodeExists(AdjListNode)
	==================================================== */
	bool Graph::nodeExists(const AdjListNode& node) const
	{
		return nodeExists(node.getLabel());
	}

	/* ====================================================
		nodeExists(string)
	==================================================== */
	bool Graph::nodeExists(const std::string& s) const
	{
		// the at() function will throw an exception if s
		// isn't in the map
		try
		{
			int index = mLabelMap.at(s);
			return true;
			
		}
		catch (std::out_of_range e)
		{
			return false;
		}
	}

	/* ====================================================
		connectedEdges(AdjListNode)
	==================================================== */
	int Graph::connectedEdges(const AdjListNode& node) const
	{
		return connectedEdges(node.getLabel());
	}

	/* ====================================================
		connectedEdges(string)
	==================================================== */
	int Graph::connectedEdges(const std::string& label) const
	{
		// Find the label's index in the graph
		try
		{
			int index = mLabelMap.at(label);
			return mGraph[index].numEdges();
		}
		catch (std::out_of_range e)
		{
			// We'll treat a label not in the graph as a "free-floating"
			// node that "exists" but is not "part" of the graph
			return 0;
		}
	}

	/* ====================================================
		numEdges()
	==================================================== */
	int Graph::numEdges() const
	{
		return mNumEdges;
	}

	/* ====================================================
		numNodes()
	==================================================== */
	int Graph::numNodes() const
	{
		return mNumNodes;
	}
}