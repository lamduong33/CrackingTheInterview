#ifndef __DATASTRUCTURES_H_
#define __DATASTRUCTURES_H_

#include <iostream>

namespace DataStructures
{
    /** A binary search tree, where the children and its descendents on the left
     ** are smaller than the parent node and the children and its descendents on
     ** the right are larger than the parent node.
     ** */
    class BinaryTree
    {
    public:
        /* Represents a single node of a tree. */
        struct TreeNode
        {
            int data;
            TreeNode* left;
            TreeNode* right;

            TreeNode() : left{nullptr}, right{nullptr} {}
            explicit TreeNode(int t_data)
                : data{t_data}, left{nullptr}, right{nullptr}
            {}
            bool isLeaf() { return (left == nullptr) && (right == nullptr); }
            bool hasBoth() { return (left != nullptr) && (right != nullptr); }
        };

    private:
        TreeNode* root;
        size_t size;

    public:
        BinaryTree() : root{nullptr}, size{0} {}
        explicit BinaryTree(const int initialValue)
            : root{new TreeNode(initialValue)}, size{1}
        {}

        size_t getSize();
        TreeNode* getRoot();

        class EmptyTreeException : public std::exception
        {
            virtual const char* what() const throw()
            {
                return "The tree is empty!";
            }
        };

        /* Check to see if the tree is a valid BST. */
        bool validTree();

        /* Check to see if all left descendants <= n < all right descendants. In
        other words, check to make sure that this is a valid binary search
        tree, given a node.*/
        bool isValid(TreeNode* node);

        /* Find the minimum element in a tree node*/
        int min(TreeNode* node);

        /* Find the maximum element in a tree node*/
        int max(TreeNode* node);

        /* Get the height of a tree, from the specified node (usually root),
        which is the number of edges from the root node to the deepest leaf
        node. */
        int getHeight(TreeNode* node);

        void insert(int t_data);

        /* Function for recursively inserting at one node, to be used by the
        insert function. This does not take balancing into account. This runtime
        is O(log n)*/
        void insert(int t_data, TreeNode* node);

        /* TODO: A BST is balanced if the two child subtrees of any node differ by at
        most one. */
        bool isBalanced();

        /* TODO: Check if a tree is complete, meaning that every level of the tree is
        fully filled, except for perhaps the last level. */
        bool isComplete(TreeNode* node);

        /* A full binary tree is a binary tree in which every node has either
        zero or two children. That is, no nodes have only one child. */
        bool fullTree();

        /* Recursive function to see if a node and all its descendents are
         * "full" */
        bool isFull(TreeNode* node);

        /* TODO: A perfect binary tree is one that is both full and ocmplete. All leaf
        nodes will be at the same level, and this level has the maximum number
        of nodes.*/
        bool isPerfect();

        /* TODO: Balance the tree */
        void balanceTree();

        /* Recursive function for printing in order*/
        void inOrderPrint(TreeNode* node);

        /* Recursive function for printing Pre-order*/
        void preOrderPrint(TreeNode* node);

        /* Recursive function for printing Post-order*/
        void postOrderPrint(TreeNode* node);

        void printInOrder();
        void printPreOrder();
        void printPostOrder();
    };
}

#endif // __DATASTRUCTURES_H_
