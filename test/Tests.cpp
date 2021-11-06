/* Unit tests using the catch2 framework for data structures for Cracking the
 * Coding Interview.
 * @author: Lam Duong */

#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp> // NOTE: assuming intalled via package manager.
//#include "catch2.hpp" // NOTE: assuming catch.hpp is in local dir
#include "../include/DataStructures.hpp"
#include "../src/Cracking.cpp"

using namespace DataStructures;

TEST_CASE("BinaryTree Order Test 1")
{
    BinaryTree bt;
    bt.insert(1);
    bt.insert(2);
    bt.insert(3);
    bt.insert(4);
    auto root = bt.getRoot();
    REQUIRE(root->data == 1);
    REQUIRE(root->right->data == 2);
    REQUIRE(root->right->right->data == 3);
    REQUIRE(root->right->right->right->data == 4);
}

TEST_CASE("BinaryTree")
{
    BinaryTree bt;
    bt.insert(230);
}

Graph makeGraph()
{
    // Graph taken from
    // https://i2.wp.com/algorithms.tutorialhorizon.com/files/2015/05/Graph-BFS.png
    Node node0("0");
    Node node1("1");
    Node node2("2");
    Node node3("3");
    Node node4("4");
    Node node5("5");
    node0.children.push_back(&node1);
    node0.children.push_back(&node2);
    node1.children.push_back(&node2);
    node1.children.push_back(&node3);
    node2.children.push_back(&node3);
    node3.children.push_back(&node4);
    node4.children.push_back(&node0);
    node4.children.push_back(&node1);
    node4.children.push_back(&node5);
    std::vector<Node*> nodes;
    nodes.push_back(&node0);
    nodes.push_back(&node1);
    nodes.push_back(&node2);
    nodes.push_back(&node3);
    nodes.push_back(&node4);
    nodes.push_back(&node5);
    Graph newGraph(nodes);
    return newGraph;
}

TEST_CASE("Cracking The Interview: Question #4.1")
{
    auto newGraph = makeGraph();
    REQUIRE(routeBetweenNodes(newGraph, newGraph.nodes[0], newGraph.nodes[1]) == true);
    REQUIRE(routeBetweenNodes(newGraph, newGraph.nodes[0], newGraph.nodes[2]) == true);
    REQUIRE(routeBetweenNodes(newGraph, newGraph.nodes[0], newGraph.nodes[3]) == true);
    REQUIRE(routeBetweenNodes(newGraph, newGraph.nodes[0], newGraph.nodes[4]) == true);
    REQUIRE(routeBetweenNodes(newGraph, newGraph.nodes[0], newGraph.nodes[5]) == true);
    REQUIRE(routeBetweenNodes(newGraph, newGraph.nodes[1], newGraph.nodes[5]) == true);
    REQUIRE(routeBetweenNodes(newGraph, newGraph.nodes[2], newGraph.nodes[5]) == true);
    REQUIRE(routeBetweenNodes(newGraph, newGraph.nodes[3], newGraph.nodes[5]) == true);
    REQUIRE(routeBetweenNodes(newGraph, newGraph.nodes[4], newGraph.nodes[5]) == true);
    REQUIRE(routeBetweenNodes(newGraph, newGraph.nodes[5], newGraph.nodes[0]) == false);
    REQUIRE(routeBetweenNodes(newGraph, newGraph.nodes[5], newGraph.nodes[1]) == false);
    REQUIRE(routeBetweenNodes(newGraph, newGraph.nodes[5], newGraph.nodes[2]) == false);
    REQUIRE(routeBetweenNodes(newGraph, newGraph.nodes[5], newGraph.nodes[3]) == false);
    REQUIRE(routeBetweenNodes(newGraph, newGraph.nodes[5], newGraph.nodes[4]) == false);
}

int main(int argc, char *argv[])
{
    int result = Catch::Session().run(argc, argv);
    return result;
}
