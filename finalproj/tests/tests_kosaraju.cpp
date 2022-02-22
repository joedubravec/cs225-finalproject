#include "../cs225/catch/catch.hpp"

#include "../graph.h"
#include "../list_class/List.h"

/* 
* These test cases test our Kosaraju implementation, this includes the reverse helper function
*/

TEST_CASE("basic reverse", "[kosaraju]") {
    Graph pleaseWork = Graph();
    pleaseWork.createNode("Eric");
    pleaseWork.createNode("Joe");
    pleaseWork.createEdge(pleaseWork.nodes[0],pleaseWork.nodes[1]);
    pleaseWork.reverseGraph();
    string edge = (*(pleaseWork.nodes[1]->edges->begin()))->artist;
    
    REQUIRE(edge == "Eric");
}

TEST_CASE("basic kosaraju", "[kosaraju]") {
    Graph pleaseWork = Graph();
    pleaseWork.createNode("0");
    pleaseWork.createNode("1");

    pleaseWork.createEdge(pleaseWork.nodes[0],pleaseWork.nodes[1]);

    REQUIRE(pleaseWork.kosaraju().size() == 0);

    pleaseWork.createEdge(pleaseWork.nodes[1],pleaseWork.nodes[0]);
    REQUIRE(pleaseWork.kosaraju().size() == 1);
}

TEST_CASE("basic 2 kosaraju", "[kosaraju]") {
    Graph pleaseWork = Graph();
    pleaseWork.createNode("0");
    pleaseWork.createNode("1");
    pleaseWork.createNode("2");

    pleaseWork.createEdge(pleaseWork.nodes[1],pleaseWork.nodes[0]);
   

   
    REQUIRE(pleaseWork.kosaraju().size() == 0);

    pleaseWork.createEdge(pleaseWork.nodes[2],pleaseWork.nodes[0]);
    REQUIRE(pleaseWork.kosaraju().size() == 0);

    pleaseWork.createEdge(pleaseWork.nodes[2],pleaseWork.nodes[1]);
    pleaseWork.createEdge(pleaseWork.nodes[0],pleaseWork.nodes[1]);
    
    REQUIRE(pleaseWork.kosaraju().size() == 1);
}

TEST_CASE("complex kosaraju", "[kosaraju]") {
    Graph pleaseWork = Graph();
    pleaseWork.createNode("0");
    pleaseWork.createNode("1");
    pleaseWork.createNode("2");
    pleaseWork.createNode("3");
    pleaseWork.createNode("4");
    pleaseWork.createNode("5");
    pleaseWork.createNode("6");
    pleaseWork.createNode("7");

    pleaseWork.createEdge(pleaseWork.nodes[0],pleaseWork.nodes[1]);
    pleaseWork.createEdge(pleaseWork.nodes[1],pleaseWork.nodes[2]);
    pleaseWork.createEdge(pleaseWork.nodes[2],pleaseWork.nodes[0]);
    pleaseWork.createEdge(pleaseWork.nodes[2],pleaseWork.nodes[3]);
    pleaseWork.createEdge(pleaseWork.nodes[3],pleaseWork.nodes[4]);
    pleaseWork.createEdge(pleaseWork.nodes[4],pleaseWork.nodes[5]);
    pleaseWork.createEdge(pleaseWork.nodes[5],pleaseWork.nodes[6]);
    pleaseWork.createEdge(pleaseWork.nodes[6],pleaseWork.nodes[4]);
    pleaseWork.createEdge(pleaseWork.nodes[4],pleaseWork.nodes[7]);
    pleaseWork.createEdge(pleaseWork.nodes[6],pleaseWork.nodes[7]);

    REQUIRE(pleaseWork.kosaraju().size() == 2);
}
