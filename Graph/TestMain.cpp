#include "Graph.h"
#include "../Algorithm/Dijkstra.h"
#include "../Algorithm/APShortestPath.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>

/* ======================================================== 
	TestMain.cpp
	- A testing file with a main() that tests the
	correctness of each class in the Graphy_Graph 
	namespace. This file also drives the test for
	the shortest path algorithm code.
======================================================== */

using namespace Graphy_Graph;

static std::string label_list[] = { "A", "B", "C", "D", "E" };
static int num_labels = 5;
static int num_edges = 8;


static int map[8][2] = { { 0, 1 }, { 0, 2 }, { 0, 3 }, { 1, 2 }, { 3, 4 }, 
					{ 4, 1 }, { 2, 2 }, { 0, 1 } };

void printGraph(Graph& theGraph)
{
	for (int i = 0; i < num_labels; ++i)
	{
		AdjList temp = theGraph.connectedEdges(label_list[i]);
		std::cout << label_list[i] << "\n";
		std::cout << "\tConnected Edges\n";
		for (AdjList::const_iterator it = temp.begin(); it != temp.end(); it++)
		{
			std::cout << "\t" << it->getLabel() << "\n";
		}
		std::cout << std::endl;
	}
}

void testCopyConstructor(Graph& theGraph)
{
	Graph copy = theGraph;
	std::cout << "--------------Test Copy Constructor--------------\n";
	std::cout << "Printing the copy...\n";
	printGraph(copy);

	std::cout << "Removing node \"" << label_list[4] << "\" from copy...\n";
	copy.removeNode(label_list[4]);

	std::cout << "Printing original graph...\n";
	printGraph(theGraph);
}

void testEdgeRemoval(Graph& theGraph)
{
	std::cout << "----------Test Edge Removal----------\n";
	std::cout << "Removing edge between \"" << label_list[0] << "\" and \"" << label_list[3] << "\"...\n";
	// Remove some edges
	int index1 = map[2][0];
	int index2 = map[2][1];
	theGraph.removeEdge(label_list[index1], label_list[index2]);

	std::cout << "Removing edge between \"" << label_list[2] << "\" and \"" << label_list[2] << "\"...\n";
	index1 = map[6][0];
	index2 = map[6][1];
	theGraph.removeEdge(label_list[index1], label_list[index2]);

	// Print all of the adjacency lists
	printGraph(theGraph);
}

void testNodeRemoval(Graph& theGraph)
{
	std::cout << "----------Test Node Removal----------\n";
	std::cout << "Removing node \"" << label_list[4] << "\"...\n";
	// Remove a node
	theGraph.removeNode(label_list[4]);
	num_labels--;

	// Print all of the adjacency lists
	printGraph(theGraph);
}

void testEdgeExists(Graph& theGraph)
{
	std::cout << "-------------Test Edge Exists--------------\n";
	std::cout << "Edge between \"" << label_list[4] << "\" and \"" << label_list[2] << "\"?: ";
	bool result = theGraph.edgeExists(label_list[4], label_list[2]);
	std::cout << result << "\n";

	std::cout << "Edge between \"" << label_list[4] << "\" and \"" << label_list[1] << "\"?: ";
	result = theGraph.edgeExists(label_list[4], label_list[1]);
	std::cout << result << "\n";
}

void testNodeExists(Graph& theGraph)
{
	std::cout << "---------------Test Node Exists--------------\n";
	std::cout << "Node \"" << label_list[0] << "\" exists?: " << theGraph.nodeExists(label_list[0]) << "\n";
	std::cout << "Node \"" << label_list[4] << "\" exists?: " << theGraph.nodeExists(label_list[4]) << "\n";
	std::cout << "Node \"" << "F" << "\" exists?: " << theGraph.nodeExists("F") << "\n";
}

// Testing graph creation and modification functionality
int main2(int argc, char** argv)
{
	//Graph theGraph(11, true);
	Graph theGraph(11, false);

	// Add all the nodes
	for (int i = 0; i < num_labels; ++i)
	{
		theGraph.addNode(label_list[i]);
	}

	// Connect some nodes
	for (int i = 0; i < num_edges; ++i)
	{
		int index1 = map[i][0];
		int index2 = map[i][1];

		theGraph.addEdge(label_list[index1], label_list[index2], 0);
	}
	
	std::cout << "Printing the graph...\n";
	printGraph(theGraph);

	testEdgeExists(theGraph);
	
	testNodeExists(theGraph);

	testCopyConstructor(theGraph);

	testEdgeRemoval(theGraph);

	testNodeRemoval(theGraph);

	testEdgeExists(theGraph);

	testNodeExists(theGraph);

	system("PAUSE");
	return EXIT_SUCCESS;
}

void printGraphMain2(Graph& graph)
{
	std::vector<AdjListNode> nodes = graph.getAllNodes();
	std::cout << "Printing Graph...\n";
	for (std::vector<AdjListNode>::iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		std::cout << "Node: " << it->getLabel() << "\n";
		AdjList edges = graph.connectedEdges(*it);
		std::cout << "Connected Edges-->\n";
		for (AdjList::iterator edgeIt = edges.begin(); edgeIt != edges.end(); edgeIt++)
		{
			std::cout << "\t" << edgeIt->getLabel() << "\n";
		}
	}
}

// Test Dijkstra's Algorithm
int main3(int argc, char** argv)
{

	// NOTE: SHIT AIN'T WORKIN' WITH A DIRECTED GRAPH
	Graph graph(13, false);

	graph.addNode("Astoria");
	graph.addNode("Seaside");
	graph.addNode("Florence");
	graph.addNode("Portland");
	graph.addNode("Salem");
	graph.addNode("Eugene");
	graph.addNode("Blue River");
	graph.addNode("The Dalles");
	graph.addNode("Bend");
	graph.addNode("Pendleton");
	graph.addNode("Burns");
	graph.addNode("Baker City");
	graph.addNode("Ontario");

	graph.addEdge("Astoria", "Seaside", 16);
	graph.addEdge("Astoria", "Portland", 95);
	graph.addEdge("Seaside", "Florence", 166);
	graph.addEdge("Florence", "Eugene", 61);
	graph.addEdge("Portland", "Salem", 46);
	graph.addEdge("Salem", "Eugene", 66);
	graph.addEdge("Portland", "The Dalles", 83);
	graph.addEdge("Eugene", "Blue River", 43);
	graph.addEdge("Blue River", "Bend", 85);
	graph.addEdge("The Dalles", "Bend", 130);
	graph.addEdge("The Dalles", "Pendleton", 126);
	graph.addEdge("Bend", "Burns", 130);
	graph.addEdge("Pendleton", "Burns", 196);
	graph.addEdge("Pendleton", "Baker City", 95);
	graph.addEdge("Baker City", "Ontario", 75);
	graph.addEdge("Ontario", "Burns", 130);

	//printGraphMain2(graph);

	AdjListNode src = graph.getNodeWithLabel("Bend");
	AdjListNode dst = graph.getNodeWithLabel("Bend");

	Graphy_Algorithm::Dijkstra driver;

	std::vector<AdjListNode> path = driver.dijkstra(graph, src, dst);

	std::cout << "-------------The Shortest Path-------------\n";
	for (std::vector<AdjListNode>::reverse_iterator it = path.rbegin(); it != path.rend(); it++)
	{
		std::cout << it->getLabel() << "\n";
	}
	system("PAUSE");
	return EXIT_SUCCESS;
}

// Test All Pairs Shortest Path
int main(int argc, char ** argv)
{
	Graph graph(13, false);

	graph.addNode("Astoria");
	graph.addNode("Seaside");
	graph.addNode("Florence");
	graph.addNode("Portland");
	graph.addNode("Salem");
	graph.addNode("Eugene");
	graph.addNode("Blue River");
	graph.addNode("The Dalles");
	graph.addNode("Bend");
	graph.addNode("Pendleton");
	graph.addNode("Burns");
	graph.addNode("Baker City");
	graph.addNode("Ontario");

	graph.addEdge("Astoria", "Seaside", 16);
	graph.addEdge("Astoria", "Portland", 95);
	graph.addEdge("Seaside", "Florence", 166);
	graph.addEdge("Florence", "Eugene", 61);
	graph.addEdge("Portland", "Salem", 46);
	graph.addEdge("Salem", "Eugene", 66);
	graph.addEdge("Portland", "The Dalles", 83);
	graph.addEdge("Eugene", "Blue River", 43);
	graph.addEdge("Blue River", "Bend", 85);
	graph.addEdge("The Dalles", "Bend", 130);
	graph.addEdge("The Dalles", "Pendleton", 126);
	graph.addEdge("Bend", "Burns", 130);
	graph.addEdge("Pendleton", "Burns", 196);
	graph.addEdge("Pendleton", "Baker City", 95);
	graph.addEdge("Baker City", "Ontario", 75);
	graph.addEdge("Ontario", "Burns", 130);
	
	std::ofstream output;
	output.open("output.txt");

	std::vector<std::vector<std::vector<AdjListNode>>> ap = 
		Graphy_Algorithm::APShortestPath::apShortestPath(graph);

	std::cout << "Finished AP Shortest Path...\n";

	output << "********************* ALL PAIRS SHORTEST PATH ***********************\n\n";
	
	int numNodes = graph.numNodes();
	for (int i = 0; i < numNodes; ++i)
	{
		output << "All paths with \"" << graph.getNodeAtIndex(i).getLabel() << "\" as the destination:\n";
		std::vector<std::vector<AdjListNode>> paths = ap[i];
		for (int j = 0; j < paths.size(); ++j)
		{
			output << "\n------------------------------------------------------\n";
			std::vector<AdjListNode> p = paths[j];
			for (int k = p.size() - 1; k >= 0; --k)
			{
				output << "\t" << p[k].getLabel() << "\n";
			}
		}

		output << "\n";
	}

	output.close();
	std::cout << "Done\n";
	system("PAUSE");
	return EXIT_SUCCESS;
}