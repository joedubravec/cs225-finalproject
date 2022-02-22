#pragma once
#include <string>
#include <vector>
#include <stack>
#include "list_class/List.h"
#include "nlohmann/json.hpp"

using std::string;
using std::vector;
using std::pair;
/*
* Directed Graph class, implemented via adjacency list
*
*/

class Graph {
    private:
        
        /*
        *Subclass for individual nodes in the graph
        */
        class GraphNode {
            public:

                /*Artist name, aka the data stored in each node*/
                string artist;

                /*Pointer to a linked list that contains every GraphNode this node points to*/
                List<GraphNode*> *edges;
                
                /*Number of edges*/
                int degree;

                /*if the node has been visited by the dfs, dfs will change to false initially and update to true */
                bool visited;

                /*interior helper for graph class*/
                void addEdge(GraphNode * toAdd);

                /*Constructors*/
                GraphNode() : artist(NULL), edges(nullptr), degree(0), visited(false) {}
                GraphNode(const string & singer) : artist(singer), edges(nullptr), degree(0), visited(false) {}
                ~GraphNode();

            private:
                void clear();
        
            
        };
        /*
        * Helper function for DFS, completes a dfs search for a connected component starting at node "node"
        * @input: node: Node from graph G to begin dfs search from
        * @input: dfsOrder: A vector of GraphNode pointers containing the current dfsOrder of the whole graph, can be empty
        * @output: Vector of GraphNode pointers in dfs order for graph G
        */
        vector<GraphNode*> dfsHelper(GraphNode* node, vector<GraphNode*> dfsOrder);
        
        /*
        * Recursive helper function for Kosaraju, completes a dfs search with a stack based implementation
        * @input: node: Node from graph G to begin dfs search from
        * @input: stackList: A stack of GraphNode pointers containing the farthest elements from start at the bottom, and closest at the top,
        *  can be empty
        * @output: stack of GraphNode pointers in containing the farthest elements from start at the bottom, and closest at the top
        */
        stack<Graph::GraphNode*> dfsHelperKosaraju(GraphNode* node, std::stack<GraphNode*> stackList);

        /*
        * Helper function for Brandes algorithm, uses a BFS-based algorithm to find all the shortest
        * paths between the source node and all other nodes and fill out the necessary data in the visited stack,
        * sigma vector, and 2d predecessors vector
        * @Input: source: the int index of the source node being used for this iteration of the calculations
        * @Input: visited: a stack of ints that stores the nodes visited in the BFS in inverse order, used for
        * centrality calcuations in brandes()
        * @Input: sigma: a vector of ints representing the number of shortest paths for each corresponding index
        * @Input: predecessors: a 2D vector where each vector contains all the predecessor nodes for the node at
        * the corresponding index
        */
        void bfsBrandes(int source, stack<int> & visited, vector<int> & sigma, vector<vector<int>> & predecessors);
        
    public:
        /*
        *   Custom destructor
        */
        ~Graph();

        /*
        * Custom Constructor to make graph
        * @input: string representation of the filepath to the json file containing the preprocesed data
        */
        Graph(string inputPath);

        /*
        * Copy Constructor to make a copy of a graph
        * @input: Graph object
        */
        Graph(const Graph & other);

        /*
        * Default Constructor to make a copy of a graph
        */
        Graph();

        /*
        * Custom Assignment operator
        */
        Graph& operator=(const Graph & rhs);

        /*
        * Helper function for custom graph constructor, loads a json file into a json object.
        * @Input: string representation of the file path to the json file containing the data set
        * @Output: Void
        */
	    void loadJson(string filepath);

        /* 
        * Creates an edge that leaves node1 and enters node2, updates graphEdges and Node1's edgeList in process
        * @Input: Node1: GraphNode pointer that edge leaves
        * @Input: Node2: GraphNode pointer that edge enters
        * @Output: Void
        */
        void createEdge(GraphNode* node1, GraphNode* node2);

        /* 
        * Creates a node using GraphNode constructors, updates Nodes list 
        * @Input: String representation of an Artist's name which will be the data stored in the node
        * @Output: Void
        */
        void createNode(string artist);

        /*
        * Finds index of a GraphNode's position in the node list
        * @Input: GraphNode pointer
        * @Output: Int index of node in node list, or -1 if not found
        */
        int getIndex(GraphNode* toFind);

        /*
        * Finds index of a GraphNode based on the data stored inside the node in the node list
        * @Input: String representation of the data stored inside of the node to find
        * @Output: Int index of node in node list, or -1 if not found
        */
        int getIndex(string toFind);

        /*
        * Finds the dfs traversal of the graph, starts from the first node in the member variable vector "nodes"
        * Uses helper function dfsHelper to deal with multiple connected components
        * @input: None
        * @Output: A vector of GraphNode pointers the represent the graph in DFS order
        */
        vector<GraphNode*> dfs();

        /*
        * Wrapper function for dfs to find the longest path between two artists in a graph
        * @input: None
        * @Output: A string in format "The longest connection is between [artist name] and [artist2 name] at a length of [path length]"
        */
        string longestConnection();

        /*vector of pointers to all nodes in graph*/
        vector<GraphNode*> nodes;

        /*number of nodes in graph*/
        size_t size;

        /*pair of nodes where the edge leaves first and enters second*/
        vector<pair<GraphNode*, GraphNode*>> graphEdges;


	    nlohmann::json data;

        /*
        * Kosaraju algorithim, takes the dfs of the graph with a stack based heplers, makes a copy of the graph with reversed edges,
        * and takes the dfs of this reversed graph to find the strongly connected components
        * @Input: None
        * @Output: A vector of vectors that contain sets of GraphNode pointers that are a strongly connected component. Only includes
        * components that have more than 1 element. 
        */ 
        vector<vector<GraphNode*>> kosaraju();

        /*Helper function for Kosaraju that reverses all the edges in a graph in place*/
        void reverseGraph();

        /*
        * Brandes algorithm. Computes the betweenness centrality of each node in nodes using an efficient
        * BFS-based algorithm (see bfsBrandes below). Betweenness centrality of a node v is defined as:
        * the sum of (# of shortest paths between two nodes s and t) / (# of those paths that pass through node v)
        * for all pairs of nodes {s, t} in the graph.
        * Returns a vector of floats, where each float is the centrality value of the corresponding node
        * in the Graph's nodes vector.
        * @Input: None
        * @Output: A vector of floats, where each element is the betweenness centrality value of the
        * corresponding node (i.e. element 0 contains the centrality of node 0)
        */
        vector<float> brandes();


};

