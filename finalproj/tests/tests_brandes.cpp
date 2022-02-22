#include "../cs225/catch/catch.hpp"

#include "../graph.h"
#include "../list_class/List.h"

#include <iostream>

/* 
* These test cases test that the Brandes algorithm is functioning properly and that it is not failing
* on edge cases, using small manually constructed examples.
*/

int getMostCentral(Graph & graph) {

    vector<float> centralities = graph.brandes();

    //prints out centralities (for testing and debugging smaller examples)
    /* std::cout << "centralities:";

    for (size_t i = 0; i < centralities.size(); i++) {
        std::cout << i << ": " << centralities[i] << " ";
    }
    std::cout << std::endl; */

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

TEST_CASE("brandes no chain", "[brandes]") {

    Graph pleaseWork = Graph();

    pleaseWork.createNode("This is a");
    pleaseWork.createNode("Certified");
    pleaseWork.createNode("Graph");
    pleaseWork.createNode("Moment");

    pleaseWork.createEdge(pleaseWork.nodes[0], pleaseWork.nodes[3]);
    pleaseWork.createEdge(pleaseWork.nodes[1], pleaseWork.nodes[3]);
    pleaseWork.createEdge(pleaseWork.nodes[2], pleaseWork.nodes[3]);

    REQUIRE (getMostCentral(pleaseWork) == 0);
}

TEST_CASE("basic brandes", "[brandes]") {

    Graph pleaseWork = Graph();
    
    pleaseWork.createNode("Eric"); //0
    pleaseWork.createNode("Joe"); //1
    pleaseWork.createNode("Ryan"); //2
    pleaseWork.createNode("Fin"); //3
    pleaseWork.createNode("Bleu"); //4

    /*

    0 -> 1 -> 2 -> 3
    |    |        /\  
    |   \/   -----|
    --> 4 --/

    */

    //expected centralities:
    // 0 - 0
    // 1 - 1
    // 2 - 0.5
    // 3 - 0
    // 4 - 1.5

    pleaseWork.createEdge(pleaseWork.nodes[0], pleaseWork.nodes[1]);
    pleaseWork.createEdge(pleaseWork.nodes[0], pleaseWork.nodes[4]);
    pleaseWork.createEdge(pleaseWork.nodes[1], pleaseWork.nodes[2]);
    pleaseWork.createEdge(pleaseWork.nodes[1], pleaseWork.nodes[4]);
    pleaseWork.createEdge(pleaseWork.nodes[2], pleaseWork.nodes[3]);
    pleaseWork.createEdge(pleaseWork.nodes[4], pleaseWork.nodes[3]);

    REQUIRE(getMostCentral(pleaseWork) == 4);
}

TEST_CASE("basic brandes disconnected", "[brandes]") {
    Graph pleaseWork = Graph();
    
    pleaseWork.createNode("Eric"); //0
    pleaseWork.createNode("Joe"); //1
    pleaseWork.createNode("Ryan"); //2
    pleaseWork.createNode("Fin"); //3
    pleaseWork.createNode("Bleu"); //4
    pleaseWork.createNode("Lando"); //5
    pleaseWork.createNode("Scrimblo"); //6

    /*

    0 -> 1 -> 2 -> 3
    |    |        /\  
    |   \/   -----|
    --> 4 --/

    5 --> 6 (floating in space wooo)

    */

    pleaseWork.createEdge(pleaseWork.nodes[0], pleaseWork.nodes[1]);
    pleaseWork.createEdge(pleaseWork.nodes[0], pleaseWork.nodes[4]);
    pleaseWork.createEdge(pleaseWork.nodes[1], pleaseWork.nodes[2]);
    pleaseWork.createEdge(pleaseWork.nodes[1], pleaseWork.nodes[4]);
    pleaseWork.createEdge(pleaseWork.nodes[2], pleaseWork.nodes[3]);
    pleaseWork.createEdge(pleaseWork.nodes[4], pleaseWork.nodes[3]);
    pleaseWork.createEdge(pleaseWork.nodes[5], pleaseWork.nodes[6]);

    REQUIRE(getMostCentral(pleaseWork) == 4);
}