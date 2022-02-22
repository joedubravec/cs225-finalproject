#include <iostream>
#include "graph.h"

using namespace std;

//helper function that utilizes brandes to find the most central artist
//(placed in a modular function to keep main as clean as possible)
int getMostCentralArtist(Graph & graph);

int main(int argc, char* argv[])
{
    // Write your own main here
    //./Data/output.json for main dataset
    //./Data/test.json for test dataset
    string path = "./Data/output.json";
    if(argc == 2) {  
        path =  argv[1];
    }
    Graph artistCollabs = Graph(path);
    
    //number of nodes in graph
    std::cout<<"There are " + to_string(artistCollabs.size) + " artists in the dataset."<<std::endl;
    //confirms size member variable and size of nodes list are the same
    std::cout<< "There are " + to_string(artistCollabs.nodes.size()) + " nodes in the graph." <<std::endl;
    //realistic number of edges considering we likely have many sets of nodes with only one edge between them
    std::cout<< "There are " + to_string(artistCollabs.graphEdges.size()) + " edges in the graph, which represent collaborations."<<std::endl;
    //dfs vector is same size indicating no extra nodes added
    std::cout<< "Running DFS visits " + to_string(artistCollabs.dfs().size()) + " unique nodes." <<std::endl;
    //Wrapper function for dfs to meet a goal!
    std::cout<< artistCollabs.longestConnection() <<std::endl;
    //No SCCs :(
    std::cout<< "Running Kosaraju's algorithm shows us there are " + to_string(artistCollabs.kosaraju().size()) + " strongly connected components." <<std::endl;
    //Brandes algorithm
    std::cout << "Most central artist is (drumroll please): " << std::endl;
    std::cout << artistCollabs.nodes[getMostCentralArtist(artistCollabs)]->artist << std::endl;

}


int getMostCentralArtist(Graph & graph) {

    vector<float> centralities = graph.brandes();

    int largestIndex = 0;
    float largestCentrality = centralities[0];
    for (size_t i = 0; i < centralities.size(); i++) {
        if (centralities[i] > largestCentrality) {
            largestCentrality = centralities[i];
            largestIndex = i;
        }
    }

    return largestIndex;
}
