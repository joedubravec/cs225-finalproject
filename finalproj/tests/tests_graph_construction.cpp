#include "../cs225/catch/catch.hpp"

#include "../graph.h"
#include "../list_class/List.h"

/* 
* These test cases test the basic functionality of our graph class, such as node construction, edge construction and
* find capabilities.
*/

TEST_CASE("basic graph", "[constructor]") {
    Graph pleaseWork = Graph();
    pleaseWork.createNode("Eric");
    pleaseWork.createNode("Joe");
    pleaseWork.createEdge(pleaseWork.nodes[0],pleaseWork.nodes[1]);
    REQUIRE(pleaseWork.nodes[0]->artist == "Eric");
}


TEST_CASE("basic edges", "[constructor]") {
    Graph pleaseWork = Graph();
    pleaseWork.createNode("Eric");
    pleaseWork.createNode("Joe");
    pleaseWork.createEdge(pleaseWork.nodes[0],pleaseWork.nodes[1]);
    string edge = (*(pleaseWork.nodes[0]->edges->begin()))->artist;
    
    REQUIRE(edge == "Joe");
}


TEST_CASE("basic unconnected", "[constructor]") {
    Graph pleaseWork = Graph();
    pleaseWork.createNode("Eric");
    pleaseWork.createNode("Joe");
    pleaseWork.createNode("Ryan");
    pleaseWork.createEdge(pleaseWork.nodes[0],pleaseWork.nodes[1]);
    string edge = (*(pleaseWork.nodes[0]->edges->begin()))->artist;
    
    REQUIRE(edge == "Joe");
    REQUIRE(pleaseWork.nodes[2]->artist == "Ryan");
}


TEST_CASE("basic chain", "[constructor]") {
    Graph pleaseWork = Graph();
    pleaseWork.createNode("Eric");
    pleaseWork.createNode("Joe");
    pleaseWork.createNode("Ryan");
    pleaseWork.createEdge(pleaseWork.nodes[0],pleaseWork.nodes[1]);
    pleaseWork.createEdge(pleaseWork.nodes[1],pleaseWork.nodes[2]);
    string edge = (*(pleaseWork.nodes[0]->edges->begin()))->artist;
    string edge2 = (*((*(pleaseWork.nodes[0]->edges->begin()))->edges->begin()))->artist;
    REQUIRE(edge == "Joe");
    REQUIRE(pleaseWork.nodes[2]->artist == "Ryan");
    REQUIRE(edge2 == "Ryan");
}


TEST_CASE("getIndex", "[constructor]") {
    Graph pleaseWork = Graph("./Data/test.json");    
    REQUIRE(pleaseWork.getIndex(pleaseWork.nodes[1]) == 1);
    REQUIRE(pleaseWork.getIndex("Joe") == 1);
}










