#ifndef _ADJLISTNODE_H_
#define _ADJLISTNODE_H_

#include <string>
namespace Graphy_Graph
{

	/* ====================================================
		CLASS: AdjListNode
		This class defines a node (vertex) in the current
		graph that is displayed in the interface. The 
		interface will define its own "node" type with
		an AdjListNode as its underlying structure.
	==================================================== */
	class AdjListNode
	{
	public:
		
		// Default constructor. Shouldn't really be used.
		AdjListNode();

		// The constructor for nodes that should be used.
		AdjListNode(const std::string&, const int index);

		// Copy constructor
		AdjListNode(const AdjListNode&);

		// Set the node's label.
		void setLabel(const std::string&);

		// Get the node's label.
		std::string getLabel() const;

		// Set the node's index.
		void setIndex(const int);

		// Get the node's index.
		int getIndex() const;

		// Overridden equality operator for AdjListNodes. Equal
		// nodes have the same label.
		bool operator ==(const AdjListNode&) const;

		// Overriden inequality operator for AdjListNodes. Unequal
		// nodes have different labels.
		bool operator !=(const AdjListNode&) const;

	private:

		// Represents the label for this node. Shown on top
		// of the node in the interface.
		std::string mLabel;

		// The index in the Graph's vector where this node's
		// adjacency list is located.
		int mIndex;

	};
}

namespace std
{
	// Need to be able to hash AdjListNodes
	template <>
	struct hash < Graphy_Graph::AdjListNode >
	{
		size_t operator()(const Graphy_Graph::AdjListNode& node) const
		{
			return hash<string>()(node.getLabel());
		}
	};
}
#endif