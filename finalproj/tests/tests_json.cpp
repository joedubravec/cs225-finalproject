#include "../cs225/catch/catch.hpp"

#include "../graph.h"
#include "../list_class/List.h"

/* 
* These test mirror many of the other tests except this test set uses a JSON data file to construct the graph.
* This test suite is a proof of concept that the real dataset, which is in json format, will work as intended 
*/

TEST_CASE("basic graph json", "[json]") {
    Graph pleaseWork = Graph("./Data/test.json");
    REQUIRE(pleaseWork.nodes[0]->artist == "Eric");
}

TEST_CASE("edges JSON", "[json]") {
    Graph pleaseWork = Graph("./Data/test.json");
    string edge = (*(pleaseWork.nodes[0]->edges->begin()))->artist;
    
    REQUIRE(edge == "Joe");
}

TEST_CASE("chain JSON", "[json]") {
    Graph pleaseWork = Graph("./Data/test.json");
    string edge = (*(pleaseWork.nodes[0]->edges->begin()))->artist;
    string edge2 = (*((*(pleaseWork.nodes[0]->edges->begin()))->edges->begin()))->artist;
    REQUIRE(edge == "Joe");
    REQUIRE(pleaseWork.nodes[2]->artist == "Ryan");
    REQUIRE(edge2 == "Ryan");
}

TEST_CASE("Complex DFS JSON", "[json]") {
    Graph pleaseWork = Graph("./Data/test.json");
    string edge = (*(pleaseWork.nodes[0]->edges->begin()))->artist;
    string edge2 = (*((*(pleaseWork.nodes[0]->edges->begin()))->edges->begin()))->artist;
    vector<string> artists;
    for (auto node : pleaseWork.dfs()) {
        artists.push_back(node->artist);
    }
    
    REQUIRE(artists[0] == "Eric");
    REQUIRE(artists[1] == "Fin");
    REQUIRE(artists[2] == "Lando");
    REQUIRE(artists[3] == "Ryan");
    REQUIRE(artists[4] == "Joe");
    REQUIRE(artists[5] == "Bleu");
}

TEST_CASE("wrapper dfs JSON", "[json]") {
    Graph pleaseWork = Graph("./Data/test.json");
    
    REQUIRE( "The longest connection is between Eric and Lando with a component size of 5, out of 2 connected components." == pleaseWork.longestConnection());
    
}

TEST_CASE("Reverse JSON", "[json]") {
    Graph pleaseWork = Graph("./Data/test.json");
    
    std::cout << "Edge list before reverse:" << std::endl;
    
    for (auto edge: pleaseWork.graphEdges) {
        std::cout << edge.first->artist << " | " << edge.second->artist <<std::endl;
    }
    pleaseWork.reverseGraph();
    
    std::cout <<  " " <<std::endl;
    std::cout << "Edge list after reverse:" << std::endl;
    
    for (auto edge: pleaseWork.graphEdges) {
        std::cout << edge.first->artist << " | " << edge.second->artist <<std::endl;
    }
    string edge = (*(pleaseWork.nodes[1]->edges->begin()))->artist;
    string edge2 = (*((*(pleaseWork.nodes[0]->edges->begin()))->edges->begin()))->artist;
    REQUIRE(edge == "Eric");
    REQUIRE(pleaseWork.nodes[2]->artist == "Ryan");
    
}

TEST_CASE("Reverse reverse works JSON", "[json]") {
    Graph pleaseWork = Graph("./Data/test.json");
    pleaseWork.reverseGraph();
    pleaseWork.reverseGraph();
    string edge = (*(pleaseWork.nodes[0]->edges->begin()))->artist;
    string edge2 = (*((*(pleaseWork.nodes[0]->edges->begin()))->edges->begin()))->artist;
    vector<string> artists;
    for (auto node : pleaseWork.dfs()) {
        artists.push_back(node->artist);
    }
    
    REQUIRE(artists[0] == "Eric");
    REQUIRE(artists[1] == "Fin");
    REQUIRE(artists[2] == "Lando");
    REQUIRE(artists[3] == "Ryan");
    REQUIRE(artists[4] == "Joe");
    REQUIRE(artists[5] == "Bleu");
    
}

TEST_CASE("kosaraju JSON", "[json]") {
    Graph pleaseWork = Graph("./Data/test.json");

    
    REQUIRE(pleaseWork.kosaraju().size() == 1);
    
}
