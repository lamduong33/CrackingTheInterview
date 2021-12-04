/* Unit tests using the catch2 framework for data structures for Cracking the
 * Coding Interview.
 * @author: Lam Duong */

#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>
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

/*
** Graph taken from
** https://i2.wp.com/algorithms.tutorialhorizon.com/files/2015/05/Graph-BFS.png
*/
Graph makeTestGraph1()
{
    auto node0 = new Node("0");
    auto node1 = new Node("1");
    auto node2 = new Node("2");
    auto node3 = new Node("3");
    auto node4 = new Node("4");
    auto node5 = new Node("5");
    node0->children.push_back(node1);
    node0->children.push_back(node2);
    node1->children.push_back(node2);
    node1->children.push_back(node3);
    node2->children.push_back(node3);
    node3->children.push_back(node4);
    node4->children.push_back(node0);
    node4->children.push_back(node1);
    node4->children.push_back(node5);
    std::vector<Node*> nodes;
    nodes.push_back(node0);
    nodes.push_back(node1);
    nodes.push_back(node2);
    nodes.push_back(node3);
    nodes.push_back(node4);
    nodes.push_back(node5);
    Graph newGraph(nodes);
    return newGraph;
}

/*
 * A disjointed graph taken from Cracking the Coding Interview on page 106
 */
Graph makeTestGraph2()
{
    auto node0 = new Node("0");
    auto node1 = new Node("1");
    auto node2 = new Node("2");
    auto node3 = new Node("3");
    auto node4 = new Node("4");
    auto node5 = new Node("5");
    auto node6 = new Node("6");
    // First set
    node0->children.push_back(node1);
    node1->children.push_back(node2);
    node2->children.push_back(node0);
    node2->children.push_back(node3);
    node3->children.push_back(node2);
    // Second set
    node4->children.push_back(node5);
    node5->children.push_back(node6);
    node6->children.push_back(node4);
    std::vector<Node*> nodes;
    nodes.push_back(node0);
    nodes.push_back(node1);
    nodes.push_back(node2);
    nodes.push_back(node3);
    nodes.push_back(node4);
    nodes.push_back(node5);
    Graph newGraph(nodes);
    return newGraph;
}

TEST_CASE("4.1 - Test 1")
{
    auto newGraph = makeTestGraph1();
    REQUIRE(routeBetweenNodes(newGraph.nodes[0], newGraph.nodes[1]) == true);
    REQUIRE(routeBetweenNodes(newGraph.nodes[0], newGraph.nodes[2]) == true);
    REQUIRE(routeBetweenNodes(newGraph.nodes[0], newGraph.nodes[3]) == true);
    REQUIRE(routeBetweenNodes(newGraph.nodes[0], newGraph.nodes[4]) == true);
    REQUIRE(routeBetweenNodes(newGraph.nodes[0], newGraph.nodes[5]) == true);
    REQUIRE(routeBetweenNodes(newGraph.nodes[1], newGraph.nodes[5]) == true);
    REQUIRE(routeBetweenNodes(newGraph.nodes[2], newGraph.nodes[5]) == true);
    REQUIRE(routeBetweenNodes(newGraph.nodes[3], newGraph.nodes[5]) == true);
    REQUIRE(routeBetweenNodes(newGraph.nodes[4], newGraph.nodes[5]) == true);
    REQUIRE(routeBetweenNodes(newGraph.nodes[5], newGraph.nodes[0]) == false);
    REQUIRE(routeBetweenNodes(newGraph.nodes[5], newGraph.nodes[1]) == false);
    REQUIRE(routeBetweenNodes(newGraph.nodes[5], newGraph.nodes[2]) == false);
    REQUIRE(routeBetweenNodes(newGraph.nodes[5], newGraph.nodes[3]) == false);
    REQUIRE(routeBetweenNodes(newGraph.nodes[5], newGraph.nodes[4]) == false);
}

TEST_CASE("4.1 - Test 2")
{
    auto newGraph = makeTestGraph2();
    REQUIRE(routeBetweenNodes(newGraph.nodes[0], newGraph.nodes[3]) == true);
    REQUIRE(routeBetweenNodes(newGraph.nodes[0], newGraph.nodes[2]) == true);
    REQUIRE(routeBetweenNodes(newGraph.nodes[6], newGraph.nodes[5]) == true);
    REQUIRE(routeBetweenNodes(newGraph.nodes[5], newGraph.nodes[4]) == true);
    REQUIRE(routeBetweenNodes(newGraph.nodes[4], newGraph.nodes[6]) == true);
    REQUIRE(routeBetweenNodes(newGraph.nodes[0], newGraph.nodes[2]) == true);
    REQUIRE(routeBetweenNodes(newGraph.nodes[0], newGraph.nodes[4]) == false);
    REQUIRE(routeBetweenNodes(newGraph.nodes[2], newGraph.nodes[5]) == false);
    REQUIRE(routeBetweenNodes(newGraph.nodes[3], newGraph.nodes[6]) == false);
}

TEST_CASE("4.2")
{
    std::vector<int> arr{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    auto tree = minimalTree(arr);
    REQUIRE(tree->data == 7);
    REQUIRE(tree->left->data == 3);
    REQUIRE(tree->right->data == 3);
}

int main(int argc, char *argv[])
{
    int result = Catch::Session().run(argc, argv);
    return result;
}
