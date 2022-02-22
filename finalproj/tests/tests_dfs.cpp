#include "../cs225/catch/catch.hpp"

#include "../graph.h"
#include "../list_class/List.h"

/* 
* These test cases test our BFS implementation
*/

TEST_CASE("basic DFS", "[dfs]") {
    Graph pleaseWork = Graph();
    pleaseWork.createNode("Eric");
    pleaseWork.createNode("Joe");
    pleaseWork.createNode("Ryan");
    pleaseWork.createNode("Fin");
    pleaseWork.createNode("Bleu");
    pleaseWork.createNode("Lando");
    pleaseWork.createEdge(pleaseWork.nodes[0],pleaseWork.nodes[1]);
    pleaseWork.createEdge(pleaseWork.nodes[1],pleaseWork.nodes[2]);
    string edge = (*(pleaseWork.nodes[0]->edges->begin()))->artist;
    string edge2 = (*((*(pleaseWork.nodes[0]->edges->begin()))->edges->begin()))->artist;
    vector<string> artists;
    for (auto node : pleaseWork.dfs()) {
        artists.push_back(node->artist);
    }
    
    REQUIRE(artists[0] == "Eric");
    REQUIRE(artists[1] == "Joe");
    REQUIRE(artists[2] == "Ryan");
    REQUIRE(artists[3] == "Fin");
    REQUIRE(artists[4] == "Bleu");
    REQUIRE(artists[5] == "Lando");
}

TEST_CASE("complex DFS", "[dfs]") {
    Graph pleaseWork = Graph();
    pleaseWork.createNode("Eric");
    pleaseWork.createNode("Joe");
    pleaseWork.createNode("Ryan");
    pleaseWork.createNode("Fin");
    pleaseWork.createNode("Bleu");
    pleaseWork.createNode("Lando");
    pleaseWork.createEdge(pleaseWork.nodes[0],pleaseWork.nodes[1]);
    pleaseWork.createEdge(pleaseWork.nodes[0],pleaseWork.nodes[2]);
    pleaseWork.createEdge(pleaseWork.nodes[0],pleaseWork.nodes[3]);
    pleaseWork.createEdge(pleaseWork.nodes[1],pleaseWork.nodes[2]);
    pleaseWork.createEdge(pleaseWork.nodes[2],pleaseWork.nodes[5]);
    pleaseWork.createEdge(pleaseWork.nodes[2],pleaseWork.nodes[0]);
    pleaseWork.createEdge(pleaseWork.nodes[2],pleaseWork.nodes[3]);
    pleaseWork.createEdge(pleaseWork.nodes[4],pleaseWork.nodes[3]);
    pleaseWork.createEdge(pleaseWork.nodes[3],pleaseWork.nodes[5]);

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

TEST_CASE("DFS Wrapper", "[dfs]") {
    Graph pleaseWork = Graph();
    pleaseWork.createNode("Eric");
    pleaseWork.createNode("Joe");
    pleaseWork.createNode("Ryan");
    pleaseWork.createNode("Fin");
    pleaseWork.createNode("Bleu");
    pleaseWork.createNode("Lando");
    pleaseWork.createEdge(pleaseWork.nodes[0],pleaseWork.nodes[1]);
    pleaseWork.createEdge(pleaseWork.nodes[0],pleaseWork.nodes[2]);
    pleaseWork.createEdge(pleaseWork.nodes[0],pleaseWork.nodes[3]);
    pleaseWork.createEdge(pleaseWork.nodes[1],pleaseWork.nodes[2]);
    pleaseWork.createEdge(pleaseWork.nodes[2],pleaseWork.nodes[5]);
    pleaseWork.createEdge(pleaseWork.nodes[2],pleaseWork.nodes[0]);
    pleaseWork.createEdge(pleaseWork.nodes[2],pleaseWork.nodes[3]);
    pleaseWork.createEdge(pleaseWork.nodes[4],pleaseWork.nodes[3]);
    pleaseWork.createEdge(pleaseWork.nodes[3],pleaseWork.nodes[5]);

    
    
    REQUIRE( "The longest connection is between Eric and Lando with a component size of 5, out of 2 connected components." == pleaseWork.longestConnection());
}
