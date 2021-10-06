#include "../include/DataStructures.hpp"
#define BOOST_TEST_MODULE CrackingTest
#include <boost/test/unit_test.hpp>

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
    bt.insert(5);
    bt.insert(6);
    bt.printPostOrder();
}
