#include "Tarjan.h"

namespace Graphy_Algorithm
{
	/* ====================================================
		tarjan(Graph)
	==================================================== */
	std::vector<std::vector<Graphy_Graph::AdjListNode>> Tarjan::tarjan(Graphy_Graph::Graph& graph)
	{
		mGraph = graph;
		mIndex = 0;
		mScc.clear();
		std::vector<Graphy_Graph::AdjListNode> nodes = graph.getAllNodes();
		int numNodes = graph.numNodes();

		// The positions of the nodes in mVertices SHOULD correspond
		// to the positions of the nodes in the actual graph
		mVertices = new struct vertex[numNodes];
		
		for (int i = 0; i < numNodes; ++i)
		{
			struct vertex v;
			v.index = UNDEFINED_INDEX;
			v.lowlink = UNDEFINED_INDEX;
			v.node = nodes[i];
			v.onStack = false;
			mVertices[i] = v;
		}

		// Here, we actually commence Tarjan's algorithm
		for (int i = 0; i < numNodes; ++i)
		{
			if (mVertices[i].index == UNDEFINED_INDEX)
			{
				strongConnect(i);
			}
		}

		// Avoid us a memory leak
		delete[] mVertices;

		return mScc;
	}

	/* ====================================================
		strongConnect(int)
	==================================================== */
	void Tarjan::strongConnect(int ind)
	{
		// Set the depth index for v to the smallest unused index
		mVertices[ind].index = mIndex;
		mVertices[ind].lowlink = mIndex;
		mIndex++;
		mStack.push(mVertices[ind]);
		mVertices[ind].onStack = true;

		Graphy_Graph::AdjList theRealEdges = mGraph.connectedEdges(mVertices[ind].node);

		// Consider successors of v
		for (Graphy_Graph::AdjList::iterator it = theRealEdges.begin(); 
				it != theRealEdges.end(); it++)
		{
			// dst node in the current edge
			int wInd = it->getIndex();
			if (mVertices[wInd].index == UNDEFINED_INDEX)
			{
				strongConnect(wInd);

				if (mVertices[wInd].lowlink <= mVertices[ind].lowlink)
				{
					mVertices[ind].lowlink = mVertices[wInd].lowlink;
				}
			}
			else if (mVertices[wInd].onStack)
			{
				if (mVertices[wInd].index <= mVertices[ind].lowlink)
				{
					mVertices[ind].lowlink = mVertices[wInd].index;
				}
			}

		}

		// If v is a root node, pop the stack, and generate a new SCC
		if (mVertices[ind].lowlink == mVertices[ind].index)
		{
			std::vector<Graphy_Graph::AdjListNode> scc;
			struct vertex w;
			do
			{
				w = mStack.top();
				mStack.pop();
				mVertices[w.node.getIndex()].onStack = false;
				scc.push_back(w.node);
			} while (mVertices[ind].node != w.node);

			// Slap the scc in the vector of scc's
			mScc.push_back(scc);
		}
	}
}