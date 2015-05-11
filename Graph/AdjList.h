
#ifndef _ADJLIST_H_
#define _ADJLIST_H_

#include <forward_list>
#include "AdjListNode.h"

namespace Graphy_Graph
{
	/* ====================================================
		CLASS: AdjList
		This class represents the adjacency list for a 
		single node in the graph. All nodes that are 
		connected to the relevant node (referred to
		in this class) are stored in the adjacency
		list.
	==================================================== */
	class AdjList
	{
	public:
		
		// Default constructor. Shouldn't really be used.
		AdjList();
		
		// The constructor that should actually be used.
		AdjList(const AdjListNode&);

		// Copy constructor
		AdjList(const AdjList&);

		// Indicates whether the adjacency list holds any nodes.
		bool empty() const;

		// Adds the specified node to this adjacency list.
		void addNode(const AdjListNode&);

		// Removes the specified node from this adjacency list.
		void removeNode(const AdjListNode&);

		AdjListNode front() const;

		// Tests specified nodes' inclusion in the adjacency list.
		bool exists(const AdjListNode&) const;

		AdjListNode getNode() const;

		// Returns the number of nodes in the adjacency list (the
		// number of edges connected to the node).
		int numEdges() const;
		
	private:

		// The internal data structure of the adjacency list is
		// a singly-linked list that is provided by the C++ STL
		std::forward_list<AdjListNode> mAdjList;

		// The node that this adjacency list actually pertains to.
		AdjListNode mNode;

		// The number of nodes that are in the adjacency list, which
		// is coincidentally the number edges that the referred node has.
		int mNumEdges;

	};
}
#endif