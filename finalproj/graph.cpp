#include "graph.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
using std::stack;

/*
* General Graph class functions including constructors/operator overrides
*
*/
Graph::Graph() {
    size = 0;
}
Graph::Graph(string inputPath) {
    size = 0;

    loadJson(inputPath);
    
    for (unsigned i = 0; i < data["artists"].size(); i++) {
        string curr = data["artists"][i]["main"];
        
        if (getIndex(curr) == -1) {
            createNode(curr);
        }

        GraphNode* currNode = nodes[getIndex(curr)];
	
	    for (unsigned j = 0; j < data["artists"][i]["featuredOn"].size(); j++) {
	        string feat = data["artists"][i]["featuredOn"][j];

	        if (getIndex(feat) == -1) {
	            createNode(feat);
	        }

	        GraphNode* featNode = nodes[getIndex(feat)];

	        createEdge(currNode, featNode);
        }
    }
}

Graph::~Graph() {
    if(!nodes.empty()) {
        for (auto node: nodes) {
            delete node;
        }
    }
    size = 0;
}

Graph::Graph(const Graph & other) {
    size = other.size;
    nodes = other.nodes;
}

Graph& Graph::operator=(const Graph & rhs) {
    delete this;

    size = rhs.size;
    nodes = rhs.nodes;
    return *this;
}

void Graph::loadJson(string filepath) {
    std::ifstream input_file(filepath);
    if (input_file.is_open()) {
        input_file >> data;
    } else {
        throw std::invalid_argument("File not found");
    }
}

void Graph::createEdge(GraphNode* node1, GraphNode* node2) {
    graphEdges.push_back(pair<GraphNode*, GraphNode*>(node1, node2));
    node1->addEdge(node2);

}

void Graph::createNode(string artist) {
    GraphNode* toReturn = new GraphNode(artist);
    nodes.push_back(toReturn);
    size++;
    
}
int Graph::getIndex(GraphNode* toFind) {
    int index = 0;
    for(auto node : nodes) {
        if (node->artist == toFind->artist) {
            return index;
        }
        index++;
    }
    return -1;
}

int Graph::getIndex(string toFind) {
    int index = 0;
    for(auto node : nodes) {
        if (node->artist == toFind) {
            return index;
        }
	index++;
    }
    return -1;
}
/*
* DFS Traversal and related/helper functions
*
*/
vector<Graph::GraphNode*> Graph::dfs() {

    vector<Graph::GraphNode*> dfsOrder;

    /* makes sure all nodes are marked as unvisited before beginning incase dfs is run multiple times*/
    for (auto node:nodes) {
        node->visited = false;
    }

    /*loops thorugh all nodes in the graph, needed incase there are multiple components*/
    for (auto node:nodes) { 
        
        /*if already visited skip*/
        if(!(node->visited)) {
            dfsOrder = dfsHelper(node, dfsOrder);
        } 
    }

    return dfsOrder;
}

vector<Graph::GraphNode*> Graph::dfsHelper(GraphNode* node, vector<GraphNode*> dfsOrder) {

    stack<Graph::GraphNode*> toCheck;
    node->visited = true;
    dfsOrder.push_back(node);

    /* if node has no edges move on*/
    if (node->edges != NULL) {
       
        /*add all of the current node's edge(s) into the stack to check*/
        for (auto connection = node->edges->begin(); connection != node->edges->end(); connection++) {

            /*avoids adding node already visited*/
            if (!((*connection)->visited)) {
                toCheck.push(*connection);
            }    
        }

        while (!toCheck.empty()) {
            GraphNode* current = toCheck.top();
            current->visited = true;
            dfsOrder.push_back(current);
            toCheck.pop();
            /*if current node has no edges move on*/
            if (current->edges != NULL) {
                
                /*add all of the current node's edges to the top of the stack, hence depth first*/ 
                for (auto temp = current->edges->begin(); temp != current->edges->end(); temp++) {
                    /*avoids adding already visited nodes*/
                    if ((*temp)->visited) {
                            continue;
                        }
                    toCheck.push(*temp);
                }
            }
        }
    }

    return dfsOrder;
}

string Graph::longestConnection() {
    string toReturn;
    stack<Graph::GraphNode*> largest;
    

    for (auto node : nodes) {
        node->visited = false;
    }
    int components = 0;
    for (auto node : nodes) {
        if (!node->visited) {
            stack<Graph::GraphNode*> temp;
            components++;
            //the use of the stack based dfs ensures that the node at the bottom of the stack is farthest away from top of stack
            temp = dfsHelperKosaraju(node, temp);
            if (temp.size()>largest.size()) {
                largest = temp;
            }
        }
        
    }
    int pathSize = largest.size();
    string artist1 = largest.top()->artist;
    largest.pop();
    string artist2;
    while (!largest.empty()) {
        artist2 = largest.top()->artist;
        largest.pop();
    }
    toReturn = "The longest connection is between " + artist1 + " and " + artist2 + " with a component size of " + to_string(pathSize) 
                + ", out of " + to_string(components) + " connected components.";
    
    return toReturn;
}
/*
* Brandes Algo and related/helper functions
*
*/

vector<float> Graph::brandes() {


    //betweenness centrality values of each node (to return)
    vector<float> betweenness;

    //set initial values
    for (auto node : nodes) {
        betweenness.push_back(0);
    }

    //2d vector of predecessors for each node
    vector<vector<int>> predecessors = vector<vector<int>>(size, vector<int>());

    //sigma[v] is the number of shortest paths from source node to v
    vector<int> sigma;

    //delta[v] is the dependency of source node on v (betweenness centrality data calculated here)
    vector<float> delta;

    //stack of visited nodes (used after bfs to get inverse order of visited nodes)
    stack<int> visited;

    //for each node in the graph
    for (size_t i = 0; i < size; i++) {

        //clear reused variables from previous loop
        for (size_t j = 0; j < size; j++) {
            predecessors[j].clear();
        }
        sigma.clear();
        sigma.resize(size, 0);
        sigma[i] = 1;
        delta.clear();
        delta.resize(size, 0);
        
        bfsBrandes(i, visited, sigma, predecessors);

        // Walk backwards from the end of the visited nodes
        while (!visited.empty()) {
            int w = visited.top();
            visited.pop();

            //For each predecessor of w, calculate centrality using filled in variables
            for (size_t j = 0; j < predecessors[w].size(); j++) {
                int v = predecessors[w][j];

                float c = ((float) sigma[v] / (float) sigma[w]) * (1.0 + delta[w]);

                delta[v] += c;

            }

            if (w != (int) i) {
                betweenness[w] += delta[w];
            }
        }

    }

    return betweenness;
}

void Graph::bfsBrandes(int source, stack<int> & visited, vector<int> & sigma, vector<vector<int>> & predecessors) {

    //distances of each traversed node from the source
    vector<int> distances = std::vector<int>(size, -1);
    distances[source] = 0;

    //here is the traditional BFS part
    queue<int> Q;
    Q.push(source);

    while(!Q.empty()) {

        int v = Q.front();
        Q.pop();

        GraphNode * curNode = nodes[v];

        //push onto stack of visited nodes (from main function)
        visited.push(v);

        if (curNode->edges != NULL) {

            for (auto neighbor = curNode->edges->begin(); neighbor != curNode->edges->end(); neighbor++) {

                int w = getIndex(*neighbor);

                //If node w hasn't been found (distance hasn't been updated),
                //Add to queue and update distance.
                if (distances[w] < 0) {
                    Q.push(w);
                    distances[w] = distances[v] + 1;
                }

                //if we are on the shortest path (only one step away from node v), add v to predecessors and update
                //the sigma vector (absolute sigma grindset)
                if (distances[w] == distances[v] + 1) {
                    predecessors[w].push_back(v);

                    sigma[w] += sigma[v];
                }
            }
        }

    }
    
}

/*
* GraphNode class methods/implementation 
*
*/
void Graph::GraphNode::addEdge(GraphNode * toAdd) {
    if (edges == nullptr) {
        edges = new List<GraphNode *>();
        
    } 
    edges->insertBack(toAdd);
    degree++;
}

Graph::GraphNode::~GraphNode() {
    this->clear();
}

/*delete helper function*/
void Graph::GraphNode::clear() {
    if (edges) {
        delete edges;
        edges = nullptr;
    }
    

}
/*
*  Kosaraju's Algorithm and related/helper functions
*
*/
void Graph::reverseGraph() {
    for (auto node: nodes) {
        delete node->edges;
        node->edges = NULL;
    }
    vector<pair<GraphNode*, GraphNode*>> copiedEdges = graphEdges;
    graphEdges.clear();
    for (auto edges: copiedEdges) {
        GraphNode* temp1 = edges.first;
        GraphNode* temp2 = edges.second;
        createEdge(temp2, temp1);
    }
}
stack<Graph::GraphNode*> Graph::dfsHelperKosaraju(GraphNode* node, stack<Graph::GraphNode*> stackList) {

    
    node->visited = true;

    /* if node has no edges move on*/
    if (node->edges != NULL) {
       
        /*recursive call on all edges of node*/
        for (auto connection = node->edges->begin(); connection != node->edges->end(); connection++) {

            /*avoids exploring node already visited*/
            if (!((*connection)->visited)) {
                stackList = dfsHelperKosaraju(*connection, stackList);
            }    
        }
    }
    stackList.push(node);
    
    return stackList;
}

vector<vector<Graph::GraphNode*>> Graph::kosaraju() {
    vector<vector<Graph::GraphNode*>> toReturn;

    for (auto node : nodes) {
        node->visited = false;
    }
    stack<Graph::GraphNode*> stack;
    for (auto node : this->nodes) {
        if (!(node->visited)) {
            stack = dfsHelperKosaraju(node, stack);
            
        }
    }

    this->reverseGraph();

    for (auto node : nodes) {
        node->visited = false;
    }

    while (!stack.empty()) {
        GraphNode* node = stack.top();
        stack.pop();
        if (!(node->visited)) {
            vector<GraphNode*> toAppend;
            toAppend = dfsHelper(node, toAppend);
            if (toAppend.size() > 1) {
                toReturn.push_back(toAppend);
            }            
        }
    }
    

    this->reverseGraph();



    return toReturn;

}
