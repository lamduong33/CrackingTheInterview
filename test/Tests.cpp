/* Unit tests using the catch2 framework for data structures for Cracking the
 * Coding Interview.
 * @author: Lam Duong */

#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp> // NOTE: assuming intalled via package manager.
//#include "catch2.hpp" // NOTE: assuming catch.hpp is in local dir
#include "../include/DataStructures.hpp"

using namespace DataStructures;

TEST_CASE("Binary Tree Order Test")
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

int main(int argc, char *argv[])
{
    int result = Catch::Session().run(argc, argv);
    return result;
}
