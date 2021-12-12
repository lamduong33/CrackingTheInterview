/* Unit tests using the catch2 framework for data structures for Cracking the
 * Coding Interview.
 * @author: Lam Duong */

#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>
#include "../include/DataStructures.hpp"
#include "../src/Cracking.cpp"

using namespace DataStructures;

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

TreeNode* makeBalancedTree()
{
    auto root = new TreeNode(8);
    root->left = new TreeNode(4);
    root->left->left = new TreeNode(2);
    root->left->left->left = new TreeNode(1);
    root->left->left->right = new TreeNode(3);
    root->left->right->left = new TreeNode(5);
    root->left->right->right = new TreeNode(7);
    root->left->right = new TreeNode(6);
    root->right = new TreeNode(12);
    root->right->left = new TreeNode(10);
    root->right->left->left = new TreeNode(9);
    root->right->left->right = new TreeNode(11);
    root->right->right->left = new TreeNode(13);
    root->right->right->right = new TreeNode(15);
    root->right->right = new TreeNode(14);
    return root;
}

/* A non-balanced tree that is not sorted.
 *      1
 *    /   \
 *   /     \
 * 2       3
 *  \     / \
 *   4   5   6
 *  /   / \
 * 7   8   9
 * */
TreeNode* makeNonBalancedTree()
{
    auto root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->left->right->left = new TreeNode(7);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(6);
    root->right->left->right = new TreeNode(9);
    root->right->left->left = new TreeNode(8);
    return root;
}

/* A linear tree that has the form of:
 * 1<-2<-3->4->5
 */
TreeNode* makeLinearTree()
{
    auto root = new TreeNode(3);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(1);
    root->right = new TreeNode(4);
    root->right->right = new TreeNode(5);
    return root;
}

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

TEST_CASE("DFSearch Test")
{
    auto testGraph = makeTestGraph1();
    REQUIRE(testGraph.DFSearch(testGraph.nodes[0], "0") == true);
    REQUIRE(testGraph.DFSearch(testGraph.nodes[0], "1") == true);
    REQUIRE(testGraph.DFSearch(testGraph.nodes[0], "2") == true);
    REQUIRE(testGraph.DFSearch(testGraph.nodes[0], "3") == true);
    REQUIRE(testGraph.DFSearch(testGraph.nodes[0], "4") == true);
    REQUIRE(testGraph.DFSearch(testGraph.nodes[0], "5") == true);
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

/* Test based on a balanced tree with depth of 4. */
TEST_CASE("4.3 - List of Depths #1")
{
    auto balancedTreeList = listOfDepths(makeBalancedTree());
    REQUIRE(balancedTreeList.size() == 4); // since depth is 4
    std::vector<int> order{8,4,12,2,6,10,14,1,3,5,7,9,11,13,15};
    auto num = 0;
    auto length = 1;

    for (auto& list : balancedTreeList)
    {
        REQUIRE(list.size() == length);
        length *= 2;
        for (auto& node : list)
        {
            REQUIRE(node->data == order[num++]);
        }
    }
}

TEST_CASE("4.3 - List of Depths #2")
{
    auto linearTreeList = listOfDepths(makeLinearTree());
    REQUIRE(linearTreeList.size() == 3); // since depth is 3
    std::vector<int> order{3,2,4,1,5};
    auto num = 0;
    auto length = 1;

    for (auto& list : linearTreeList)
    {
        REQUIRE (list.size() == length);
        if (length == 1) length = 2;
        for (auto& node : list)
        {
            REQUIRE(node->data == order[num++]);
        }
    }
}

TEST_CASE("4.3 - List of Depths #3")
{
    auto nonBalancedList = listOfDepths(makeNonBalancedTree());
    REQUIRE(nonBalancedList.size() == 3); // since depth is 3
    std::vector<int> order{1,2,3,4,5,6,7,8,9};
    std::vector<int> lengthOrder{1,2,3,3};
    auto num = 0;
    auto length = 0;

    for (auto& list : nonBalancedList)
    {
        REQUIRE (list.size() == lengthOrder[length]);
        for (auto& node : list)
        {
            REQUIRE(node->data == order[num++]);
        }
    }
}


int main(int argc, char *argv[])
{
    int result = Catch::Session().run(argc, argv);
    return result;
}
