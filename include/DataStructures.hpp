/* NOTE: Data structures were made using raw pointers for quick implementation
 * and learning purposes.
 * @author: Lam Duong
 */

#ifndef __DATASTRUCTURES_H_
#define __DATASTRUCTURES_H_

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <queue>
#include <unordered_set>

namespace DataStructures
{

/* Represents a node of a graph and it is directed. */
struct Node
{
    std::string name;
    std::vector<Node*> children;
    Node(std::string t_name) : name{t_name} {}
};

/* Represents a basic tree */
struct Tree
{
    Node* root;
};

/* Represents a linked list node */
struct LinkedListNode
{
    LinkedListNode* next = nullptr;
    int data;
};

/* Represents a graph with a list of nodes. This is essentially an adjacency
 * list. This graph is a directed graph.*/
struct Graph
{
    std::vector<Node*> nodes;
    Graph(std::vector<Node*> t_node) : nodes{t_node} {}
    bool DFSearch(Node* root, std::string value);
    bool recursiveDFS(Node* root, std::string value, std::unordered_set<Node*>& visited);
    bool BFSearch(Node* root, std::string value);
};

/* Class for a simple linked list */
struct DoublyLinkedNode
{
    DoublyLinkedNode *next = nullptr;
    DoublyLinkedNode *previous = nullptr;
    int data;

    explicit DoublyLinkedNode(int t_data) : data{t_data} {}
    explicit DoublyLinkedNode(std::vector<int> &list) : data{list[0]}
    {
        auto it = this;
        for (int i = 1; i < (int)list.size(); i++)
        {
            it->next = new DoublyLinkedNode(list[i]);
            it->next->previous = it;
            it = it->next;
        }
    }

    /* Traverse the list and append to the end.*/
    void appendToTail(int t_data);

    void joinList(DoublyLinkedNode *anotherList);

    DoublyLinkedNode *deleteNode(DoublyLinkedNode *t_head, int t_data);

    void printList();
};

/* Stack data structure */
class Stack
{
public:
    class StackNode
    {
        int data;
        StackNode *next;

    public:
        explicit StackNode() : data{0}, next{nullptr} {}
        explicit StackNode(int t_data) : data{t_data}, next{nullptr} {}
        explicit StackNode(int t_data, StackNode *t_next)
            : data{t_data}, next{t_next}
        {
        }

        ~StackNode() {}
        int getData() { return data; }
        StackNode *getNext() { return this->next; }
        void setNext(StackNode *t_next) { this->next = t_next; }
    };

    StackNode *top;
    int size = 0;
    class EmptyStackException : public std::exception
    {
        virtual const char *what() const throw() { return "Empty stack!"; }
    };

    int pop();
    void push(int t_data);
    int peek();
    bool isEmpty();
    void printStack();
};

/* The queue class is FIFO (first in first out). Notice that this requires a
 * template class, */
template <class T> class Queue
{
private:
    struct QueueNode
    {
        T data;
        QueueNode *next;
        explicit QueueNode(T t_data) : data{t_data}, next{nullptr} {}
    };
    QueueNode *first;
    QueueNode *last;

public:
    Queue();
    class NoSuchElementException : public std::exception
    {
        virtual const char *what() const throw()
        {
            return "No such element in queue!";
        }
    };

    void add(T item);
    T remove();
    T peekFirst();
    T peekLast();
    bool isEmpty();
};

/* Represents a single node of a tree. */
struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : left{nullptr}, right{nullptr} {}
    explicit TreeNode(int t_data)
        : data{t_data}, left{nullptr}, right{nullptr}
    {
    }

    bool isLeaf() { return (left == nullptr) && (right == nullptr); }
    bool hasBoth() { return (left != nullptr) && (right != nullptr); }
    std::string treeString(); // TODO: Finish this
};

/** A binary search tree, where the children and its descendents on the left
 ** are smaller than the parent node and the children and its descendents on
 ** the right are larger than the parent node.
 ** */
class BinaryTree
{
    TreeNode *root;
    size_t size;
public:
    BinaryTree() : root{nullptr}, size{0} {}
    explicit BinaryTree(const int initialValue)
        : root{new TreeNode(initialValue)}, size{1}
    {
    }

    size_t getSize();
    TreeNode *getRoot();

    class EmptyTreeException : public std::exception
    {
        virtual const char *what() const throw() { return "The tree is empty!"; }
    };

    /* Check to see if the tree is a valid BST. */
    bool validTree();

    /* Check to see if all left descendants <= n < all right descendants. In
    other words, check to make sure that this is a valid binary search
    tree, given a node.*/
    bool isValid(TreeNode *node);

    /* Find the minimum element in a tree node*/
    int min(TreeNode *node);

    /* Find the maximum element in a tree node*/
    int max(TreeNode *node);

    /* Get the height of a tree, from the specified node (usually root),
    which is the number of edges from the root node to the deepest leaf
    node. */
    int getHeight(TreeNode *node);

    /* Inserting one element in the tree. This consists of calling the
    recursive function with the same name (overridden), which is O(log n).
    Balancing the tree after the recursive function is O(n) worst case.*/
    void insert(int t_data);

    /* Function for recursively inserting at one node, to be used by the
    insert function. This does not take balancing into account. This runtime
    is O(log n)*/
    void insert(int t_data, TreeNode *node);

    TreeNode* childrenHave(int t_data, TreeNode* node);

    /* Determine if the BinaryTree has the given value in it.*/
    bool contains(int t_data);

    /* Recursively determine whether if the given data is in the tree node or
     * not. */
    bool in(int t_data, TreeNode* node);

    /* TODO: A BST is balanced if the two child subtrees of any node differ by at
    most one. */
    bool balanced();

    /* TODO: Check if a tree is complete, meaning that every level of the tree is
    fully filled, except for perhaps the last level. */
    bool isComplete(TreeNode *node);

    /* A full binary tree is a binary tree in which every node has either
    zero or two children. That is, no nodes have only one child. */
    bool fullTree();

    /* Recursive function to see if a node and all its descendents are
     * "full" */
    bool isFull(TreeNode *node);

    /* TODO: A perfect binary tree is one that is both full and ocmplete. All
    leaf nodes will be at the same level, and this level has the maximum number
    of nodes.*/
    bool isPerfect();

private:

    /* Recursive function for printing in order*/
    void inOrderPrint(TreeNode *node);

    /* Recursive function for printing Pre-order*/
    void preOrderPrint(TreeNode *node);

    /* Recursive function for printing Post-order*/
    void postOrderPrint(TreeNode *node);

public:
    void printInOrder();
    void printPreOrder();
    void printPostOrder();
};

/*
** A Binary Search Tree is simply a binary tree that is sorted. This tree is
** also balanced as well.
*/
class BinarySearchTree : public BinaryTree
{
    /* Search recursively for the minimum element. This more efficient since a
     * BST is sorted already and it is the leftmost element.*/
    int min(TreeNode* node);

    /* Search recursively for the maximum element. This more efficient since a
     * BST is sorted already and it is the rightmost element.*/
    int max(TreeNode* node);

    /* Insert the element into the BST and balance the tree. */
    void insert(int t_data);

    /* TODO: Balance the tree */
    void balanceTree();

    /* Remove the first node encountered with the same data in the tree. */
    void remove(int t_data);

    /* TODO: Recursively remove the first node encountered with the same data
     * in the tree node. */
    TreeNode* remove(int t_data, TreeNode* node);

};

struct MinHeap : public BinaryTree
{
    /* TODO: Implement the overriden recursive function for MinHeap. */
    void insert(int t_data, TreeNode* node);
    int extract_min();
};

} // namespace DataStructures

#endif // __DATASTRUCTURES_H_
