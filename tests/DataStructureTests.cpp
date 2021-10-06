#define BOOST_TEST_MODULE CrackingTest
#include <boost/test/unit_test.hpp>
#include "../include/DataStructures.hpp"

using namespace DataStructures;

BOOST_AUTO_TEST_CASE(TreeTest)
{
    BinaryTree bt;
    BOOST_CHECK(bt.validTree());
    bt.isFull(bt.getRoot());
    bt.insert(1);
    bt.insert(2);
    bt.insert(3);
    bt.insert(4);
    auto root = bt.getRoot();
    BOOST_CHECK(root->data == 1);
    BOOST_CHECK(root->right->data == 2);
    BOOST_CHECK(root->right->right->data == 3);
    BOOST_CHECK(root->right->right->right->data == 4);
}
