
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <map>
#include <list>
#include <exception>
#include "AdjList.h"

namespace Graphy_Graph
{
	/* ====================================================
		CLASS: Graph
		This class defines the entire graph as a vector
		of adjacency lists for each node in the graph.
		Other modules in Graphy will use and modify the
		current graph with the member functions provided
		in this class.
	==================================================== */
	class Graph
	{
	public:

		// Default constructor that creates an empty (undirected) graph.
		Graph();

		// Constructor that creates a graph optimized for the specified size.
		// directed = true indicates that edges "flow" in only one direction.
		Graph(int capacity, bool directed);

		// Copy constructor
		Graph(const Graph&);

		// Add a node to the graph.
		void addNode(const AdjListNode&);

		// Add a node with the given label to the graph.
		void addNode(const std::string&);

		// Remove a node from the graph (and all of its edges).
		void removeNode(const AdjListNode&);

		// Remove a node with the given label from the graph (and all of its edges).
		void removeNode(const std::string&);

		// Add an edge between the two specified nodes.
		// For directed graphs, edge starts at "src" and ends at "dst".
		// The edge will have the specified cost.
		void addEdge(const AdjListNode& src, const AdjListNode& dst, int cost);

		// Add an edge between the two nodes with the specified labels.
		// For directed graphs, edge starts at "src" and ends at "dst".
		// The edge will have the specified cost.
		void addEdge(const std::string& src, const std::string& dst, int cost);

		// Remove the edge between the specified nodes. If the graph is
		// directed, the edge from the first paramter to the second
		// parameter will be removed (if it exists).
		void removeEdge(const AdjListNode&, const AdjListNode&);

		// Remove the edge between the two nodes with the specified labels.
		// If the graph is directed, the edge from the first parameter
		// to the second parameter will be removed (if it exists).
		void removeEdge(const std::string&, const std::string&);

		// Test whether an edge exists between the two given nodes.
		// NOTE: If the graph is directed, the first argument is the source,
		// and the second argument is the destination node.
		bool edgeExists(const AdjListNode& src, const AdjListNode& dst) const;

		// Test whether an edge exists between the two nodes with the given labels.
		// NOTE: If the graph is directed, the first argument is the source,
		// and the second argument is the destination node.
		bool edgeExists(const std::string& src, const std::string& dst) const;

		// Test whether the given node is in the graph.
		bool nodeExists(const AdjListNode&) const;

		// Test whether a node with the given label is in the graph.
		bool nodeExists(const std::string&) const;

		// Return the adjacency list for the given node (if any).
		AdjList connectedEdges(const AdjListNode&);

		// Return the adjacency list for the node with the given label (if any).
		AdjList connectedEdges(const std::string&);

		// Return a list of all of the nodes in the graph.
		std::vector<AdjListNode> getAllNodes() const;

		// Get the node with the specified index.
		// WARNING: Undefined behavior if index is invalid.
		AdjListNode getNodeAtIndex(int index) const;

		// Get the node with the specified label.
		// WARNING: Undefined behavior if label is invalid.
		AdjListNode getNodeWithLabel(const std::string& s) const;

		// Return the total number of edges in the graph.
		int numEdges() const;

		// Return the total number of nodes in the graph.
		int numNodes() const;
	private:

		// The vector of adjacency lists that implicitly defines this graph.
		std::vector<AdjList> mGraph;

		// A hashtable that maps node labels to indices in the vector.
		std::map<std::string, int> mLabelMap;

		// The number of nodes in the graph.
		int mNumNodes;

		// The number of edges in the graph.
		int mNumEdges;

		// Indicates whether this is a directed graph.
		bool mDirected;
	};
}
#endif