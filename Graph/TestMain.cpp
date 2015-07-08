#include "Graph.h"
#include "../Algorithm/Dijkstra.h"
#include "../Algorithm/APShortestPath.h"
#include "../Algorithm/Tarjan.h"
#include "../Algorithm/Mst.h"
#include "../Algorithm/GraphColor.h"
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

	//Graphy_Algorithm::Dijkstra driver;

	//std::vector<AdjListNode> path = driver.dijkstra(graph, src, dst);

	/*std::cout << "-------------The Shortest Path-------------\n";
	for (std::vector<AdjListNode>::reverse_iterator it = path.rbegin(); it != path.rend(); it++)
	{
		std::cout << it->getLabel() << "\n";
	}*/
	system("PAUSE");
	return EXIT_SUCCESS;
}

// Test All Pairs Shortest Path
int main5(int argc, char ** argv)
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

// Test Tarjan's Algorithm to find strongly-connected components
int main4(int argc, char ** argv)
{
	Graph graph(8, true);

	graph.addNode("A");
	graph.addNode("B");
	graph.addNode("C");
	graph.addNode("D");
	graph.addNode("E");
	graph.addNode("F");
	graph.addNode("G");
	graph.addNode("H");
	/*graph.addNode("I");
	graph.addNode("J");
	graph.addNode("K");
	graph.addNode("L");*/

	graph.addEdge("A", "B", 0);
	graph.addEdge("C", "A", 0);
	graph.addEdge("B", "C", 0);
	graph.addEdge("B", "D", 0);
	graph.addEdge("D", "C", 0);
	graph.addEdge("B", "E", 0);
	graph.addEdge("D", "E", 0);
	graph.addEdge("E", "F", 0);
	graph.addEdge("E", "H", 0);
	graph.addEdge("E", "G", 0);
	graph.addEdge("F", "G", 0);
	graph.addEdge("G", "H", 0);
	graph.addEdge("H", "F", 0);

	/*graph.addEdge("B", "A", 0);
	graph.addEdge("B", "E", 0);
	graph.addEdge("D", "B", 0);
	graph.addEdge("C", "B", 0);
	graph.addEdge("C", "F", 0);
	graph.addEdge("E", "B", 0);
	graph.addEdge("F", "C", 0);
	graph.addEdge("F", "E", 0);
	graph.addEdge("G", "E", 0);
	graph.addEdge("G", "I", 0);
	graph.addEdge("H", "G", 0);
	graph.addEdge("H", "F", 0);
	graph.addEdge("I", "J", 0);
	graph.addEdge("J", "G", 0);
	graph.addEdge("J", "L", 0);
	graph.addEdge("K", "H", 0);
	graph.addEdge("L", "K", 0);*/

	Graphy_Algorithm::Tarjan tarjan;

	// NOTE: SHIT AIN'T WORKIN'
	std::vector<std::vector<AdjListNode>> scc = tarjan.tarjan(graph);

	std::cout << "***************Strongly Connected Components****************\n\n";

	for (std::vector<std::vector<AdjListNode>>::iterator it = scc.begin(); it != scc.end(); it++)
	{ 
		std::cout << "---------------------------------------------\n";
		for (std::vector<AdjListNode>::iterator it2 = it->begin(); it2 != it->end(); it2++)
		{
			std::cout << it2->getLabel() << "\n";
		}
	}
	system("PAUSE");
	return EXIT_SUCCESS;
}

// Test (inefficient) graph coloring
int main69(int argc, char ** argv)
{

	Graph graph(38, false);

	// Stupidly ugly code follows
	
	graph.addNode("1");
	graph.addNode("2");
	graph.addNode("3");
	graph.addNode("4");
	graph.addNode("5");
	graph.addNode("6");
	graph.addNode("7");
	graph.addNode("8");
	graph.addNode("9");
	graph.addNode("10");
	graph.addNode("11");
	graph.addNode("12");
	graph.addNode("13");
	graph.addNode("14");
	graph.addNode("15");
	graph.addNode("16");
	graph.addNode("17");
	graph.addNode("18");
	graph.addNode("19");
	graph.addNode("20");
	graph.addNode("21");
	graph.addNode("22");
	graph.addNode("23");
	graph.addNode("24");
	graph.addNode("25");
	graph.addNode("26");
	graph.addNode("27");
	graph.addNode("28");
	graph.addNode("29");
	graph.addNode("30");
	graph.addNode("31");
	graph.addNode("32");
	graph.addNode("33");
	graph.addNode("34");
	graph.addNode("35");
	graph.addNode("36");
	graph.addNode("37");
	graph.addNode("38");

	graph.addEdge("1", "5", 0);
	graph.addEdge("1", "3", 0);
	graph.addEdge("1", "29", 0);
	graph.addEdge("1", "8", 0);
	graph.addEdge("1", "2", 0);
	graph.addEdge("1", "11", 0);

	graph.addEdge("2", "3", 0);
	graph.addEdge("2", "8", 0);
	graph.addEdge("2", "6", 0);
	graph.addEdge("2", "14", 0);
	graph.addEdge("2", "27", 0);
	graph.addEdge("2", "30", 0);
	graph.addEdge("2", "26", 0);
	graph.addEdge("2", "16", 0);
	graph.addEdge("2", "31", 0);
	graph.addEdge("2", "12", 0);
	graph.addEdge("2", "34", 0);
	graph.addEdge("2", "4", 0);

	graph.addEdge("3", "4", 0);
	graph.addEdge("3", "10", 0);
	graph.addEdge("3", "15", 0);
	graph.addEdge("3", "22", 0);
	graph.addEdge("3", "17", 0);

	graph.addEdge("4", "28", 0);
	graph.addEdge("4", "9", 0);
	graph.addEdge("4", "7", 0);
	graph.addEdge("4", "5", 0);
	graph.addEdge("4", "12", 0);
	graph.addEdge("4", "32", 0);
	graph.addEdge("4", "23", 0);
	graph.addEdge("4", "18", 0);

	graph.addEdge("5", "7", 0);
	graph.addEdge("5", "20", 0);
	graph.addEdge("5", "17", 0);
	graph.addEdge("5", "19", 0);

	graph.addEdge("6", "5", 0);

	graph.addEdge("7", "9", 0);
	graph.addEdge("7", "13", 0);
	graph.addEdge("7", "21", 0);

	graph.addEdge("8", "27", 0);
	graph.addEdge("8", "10", 0);
	graph.addEdge("8", "24", 0);
	graph.addEdge("8", "15", 0);
	graph.addEdge("8", "29", 0);

	graph.addEdge("9", "11", 0);

	graph.addEdge("10", "14", 0);
	graph.addEdge("10", "37", 0);

	graph.addEdge("11", "25", 0);
	graph.addEdge("11", "32", 0);
	graph.addEdge("11", "34", 0);
	graph.addEdge("11", "13", 0);

	graph.addEdge("12", "35", 0);
	graph.addEdge("12", "16", 0);
	graph.addEdge("12", "26", 0);

	graph.addEdge("13", "18", 0);
	graph.addEdge("13", "35", 0);
	graph.addEdge("13", "19", 0);

	graph.addEdge("14", "20", 0);
	graph.addEdge("15", "36", 0);
	graph.addEdge("17", "33", 0);
	graph.addEdge("18", "25", 0);
	graph.addEdge("19", "23", 0);
	graph.addEdge("19", "21", 0);
	graph.addEdge("20", "37", 0);
	graph.addEdge("21", "31", 0);

	graph.addEdge("22", "13", 0);
	graph.addEdge("22", "24", 0);
	graph.addEdge("22", "36", 0);

	graph.addEdge("28", "25", 0);

	graph.addEdge("27", "30", 0);

	graph.addEdge("29", "33", 0);
	graph.addEdge("31", "38", 0);
	graph.addEdge("34", "38", 0);
	

	/*graph.addNode("A");
	graph.addNode("B");
	graph.addNode("C");
	graph.addNode("D");
	graph.addNode("E");
	graph.addNode("F");

	graph.addEdge("A", "B", 0);
	graph.addEdge("A", "C", 0);
	graph.addEdge("A", "D", 0);
	graph.addEdge("A", "E", 0);

	graph.addEdge("B", "C", 0);
	graph.addEdge("B", "D", 0);
	graph.addEdge("B", "F", 0);

	graph.addEdge("C", "E", 0);
	graph.addEdge("C", "F", 0);

	graph.addEdge("D", "E", 0);
	graph.addEdge("D", "F", 0);

	graph.addEdge("E", "F", 0);*/

	std::vector<struct Graphy_Algorithm::ColorNode> coloredNodes = 
		Graphy_Algorithm::GraphColor::colorGraph(graph, 3);

	if (!coloredNodes.empty())
	{
		std::cout << "Graph is 3-colorable\n";

		for (std::vector<struct Graphy_Algorithm::ColorNode>::iterator it = coloredNodes.begin();
			it != coloredNodes.end(); it++)
		{
			std::cout << "Node: " << it->node.getLabel() << "; Color: " << it->color << "\n";
		}
	}
	else
	{
		std::cout << "Graph is NOT 3-colorable\n";
	}

	printGraphMain2(graph);
	
	system("PAUSE");
	return EXIT_SUCCESS;
}

// Test Minimum Spanning Tree
int main6(int argc, char ** argv)
{
	Graph graph(7, false);

	graph.addNode("A");
	graph.addNode("B");
	graph.addNode("C");
	graph.addNode("D");
	graph.addNode("E");
	graph.addNode("F");
	graph.addNode("G");

	graph.addEdge("A", "B", 5);
	graph.addEdge("B", "C", 13);
	graph.addEdge("A", "D", 17);
	graph.addEdge("B", "D", 12);
	graph.addEdge("B", "G", 8);
	graph.addEdge("C", "G", 11);
	graph.addEdge("C", "E", 6);
	graph.addEdge("D", "F", 10);
	graph.addEdge("D", "G", 8);
	graph.addEdge("E", "G", 14);
	graph.addEdge("F", "G", 4);


	// Now, run the mst algy
	Graph minSpan = Graphy_Algorithm::Mst::mst(graph);

	// Now, just print out the minimum spanning tree
	printGraphMain2(minSpan);
	system("PAUSE");
	return EXIT_SUCCESS;
}