#ifndef _TARJAN_H_
#define _TARJAN_H_

#include "../Graph/Graph.h"
#include <stack>

namespace Graphy_Algorithm
{
	// A simple type to hold node-specific information that
	// is needed for the strongly-connected components algorithm.
	struct vertex
	{
		Graphy_Graph::AdjListNode node;
		int index;
		bool onStack;
		int lowlink;
	};

#define UNDEFINED_INDEX -1

	/* ====================================================
		CLASS: Tarjan
		--> Compute the strongly-connected components of
		a graph using Tarjan's algorithm.
	==================================================== */
	class Tarjan
	{
	public:
		// This function takes as input a Graphy graph and returns
		// a vector of partitions that represent the strongly-connected
		// components of the graph. Tarjan's algorithm is used
		// to find the strongly-connected components.
		std::vector<std::vector<Graphy_Graph::AdjListNode>> tarjan(Graphy_Graph::Graph& graph);

	private:

		// Helper function that is used in Tarjan's algorithm.
		void strongConnect(int ind);

		// Stack of nodes maintained during the running of Tarjan's algorithm.
		std::stack<struct vertex> mStack;

		// A running index that is used during the execution of Tarjan's algorithm.
		int mIndex;

		// A heap-allocated array that holds all of the "vertices" at runtime.
		struct vertex * mVertices;

		// Holds all of the strongly-connected components at the end of the algorithm.
		std::vector<std::vector<Graphy_Graph::AdjListNode>> mScc;

		// The graph that we are working on
		Graphy_Graph::Graph mGraph;
	};
}

#endif