
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

		// Create custom iterator so we don't have to expose
		// the underlying data structure
		typedef std::forward_list<AdjListNode>::iterator iterator;
		typedef std::forward_list<AdjListNode>::const_iterator const_iterator;
		
		// Default constructor. Shouldn't really be used.
		AdjList();
		
		// The constructor that should actually be used.
		AdjList(const AdjListNode&);

		// Copy constructor
		AdjList(const AdjList&);

		// Indicates whether the adjacency list holds any nodes.
		bool empty() const;

		// Adds the specified node to this adjacency list.
		void addNode(const AdjListNode&, int);

		// Removes the specified node from this adjacency list.
		void removeNode(const AdjListNode&);

		// Retrieve the first node in the adjacency list
		AdjListNode front() const;

		// Tests specified nodes' inclusion in the adjacency list.
		bool exists(const AdjListNode&) const;

		// Return the node that this list actually pertains to.
		AdjListNode getNode() const;

		// Return the ordered list of costs for this adjacency list.
		std::forward_list<int> getCostList() const;

		// Returns the number of nodes in the adjacency list (the
		// number of edges connected to the node).
		int numEdges() const;

		// Functions for the custom iterator
		iterator begin() { return mAdjList.begin(); }
		iterator end() { return mAdjList.end(); }
		const_iterator begin() const { return mAdjList.begin(); }
		const_iterator end() const { return mAdjList.end(); }
		
	private:

		// The internal data structure of the adjacency list is
		// a singly-linked list that is provided by the C++ STL.
		std::forward_list<AdjListNode> mAdjList;

		// The data structure that corresponds to the cost of each edge.
		std::forward_list<int> mCostList;

		// The node that this adjacency list actually pertains to.
		AdjListNode mNode;

		// The number of nodes that are in the adjacency list, which
		// is coincidentally the number edges that the referred node has.
		int mNumEdges;

	};
}
#endif