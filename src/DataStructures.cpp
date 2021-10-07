#include "../include/DataStructures.hpp"

using namespace DataStructures;

/*-------------------------------LINKED LIST---------------------------------*/

/* Traverse the list and append to the end.*/
void Node::appendToTail(int t_data)
{
    auto end = new Node(t_data);
    auto n = this;
    while (n->next != nullptr)
    {
        n = n->next;
    }
    n->next = end;
    end->previous = n;
}

/*Join the current list with another list*/
void Node::joinList(Node *anotherList)
{
    auto n = this;
    while (n->next != nullptr)
    {
        n = n->next;
    }
    n->next = anotherList;
    anotherList->previous = n;
}

/* Delete the first node that contains t_data in the list given by t_head */
Node *Node::deleteNode(Node *t_head, int t_data)
{
    auto n = t_head;
    if (n->data == t_data)
    {
        t_head->next->previous = nullptr;
        return t_head->next; // head moved
    }

    while (n->next != nullptr)
    {
        if (n->next->data == t_data)
        {
            n->next = n->next->next;
            n->next->next->previous = n;
            return t_head; // head didn't change
        }
        n = n->next;
    }
    return t_head;
}

/*Print the list iteratively */
void Node::printList()
{
    auto it = this;
    while (it != nullptr)
    {
        std::cout << it->data;
        it = it->next;
    }
}

/*-------------------------------STACK---------------------------------------*/

/* Remove the node and return the value contained by that node. */
int Stack::pop()
{
    if (top == nullptr)
        throw new EmptyStackException;
    int item = top->getData();
    top = top->getNext();
    size--;
    return item;
}

/* Create a new node and push it onto stack with the given data */
void Stack::push(int t_data)
{
    auto t = new StackNode(t_data);
    t->setNext(top);
    top = t;
    size++;
}

/* Return the value on the top of the stack. Throw an exception if the stack is
 * empty */
int Stack::peek()
{
    if (top == nullptr)
        throw new EmptyStackException;
    return top->getData();
}

/*Check to see if the stack is empty. */
bool Stack::isEmpty() { return (size == 0); }

/*Print the stack iteratively. */
void Stack::printStack()
{
    auto head = top;
    for (auto i = 0; i < size; i++)
    {
        std::cout << head->getData();
        if (i != size - 1)
            std::cout << "->";
        head = head->getNext();
    }
    std::cout << std::endl;
}

/*-------------------------------QUEUE---------------------------------------*/

/*Add to the queue with a given item*/
template <class T> void Queue<T>::add(T item)
{
    auto t = new QueueNode(item);
    if (last != nullptr)
        last->next = t;
    last = t;
    if (first == nullptr)
        first = last;
}

/*Remove the node from the queue and return the data that node contains.*/
template <class T> T Queue<T>::remove()
{
    if (first == nullptr)
        throw new NoSuchElementException;
    T data = first->data;
    first = first->next;
    if (first == nullptr)
    {
        delete (last);
        last = nullptr;
    }
    return data;
}

/* Show the first element on the queue. */
template <class T> T Queue<T>::peekFirst()
{
    if (first == nullptr)
        throw new NoSuchElementException;
    return first->data;
}

/* Show the last element on the queue. */
template <class T> T Queue<T>::peekLast()
{
    if (first == nullptr)
        throw new NoSuchElementException;
    return last->data;
}

/*Determine if the queue is empty. Throw an exception if either first or last is
 *null but the other is not. */
template <class T> bool Queue<T>::isEmpty()
{
    if ((first == nullptr) != (last == nullptr))
        throw new std::exception; // Invalid state
    return (first == nullptr);
}

/*-------------------------------BINARY TREE---------------------------------*/

/*Return the size of how many nodes are in the tree. */
size_t BinaryTree::getSize() { return this->size; }

/*Get the TreeNode that is at the root of the binary tree.*/
TreeNode *BinaryTree::getRoot() { return this->root; }

/* Check to see if the tree is a valid BST. */
bool BinaryTree::validTree() { return isValid(this->root); }

/* Check to see if all left descendants <= n < all right descendants. In
other words, check to make sure that this is a valid binary search
tree, given a node.*/
bool BinaryTree::isValid(TreeNode *node)
{
    auto result = true;
    if (node == nullptr)
        return result;
    if (node->isLeaf())
        return result;
    if (node->left != nullptr && (max(node->left) > node->data))
    {
        result = false;
    }
    if (result && node->right != nullptr && (min(node->right) < node->data))
    {
        result = false;
    }
    if (!isValid(node->left) || !isValid(node->right))
        result = false;
    return result;
}

/* Find the minimum element in a tree node*/
int BinaryTree::min(TreeNode *node)
{
    if (node == nullptr)
        throw new EmptyTreeException;
    auto minimum = node->data;
    if (!node->isLeaf())
    {
        if (node->left != nullptr)
        {
            auto leftMin = min(node->left);
            minimum = leftMin < minimum ? leftMin : minimum;
        }
        if (node->right != nullptr)
        {
            auto rightMin = min(node->right);
            minimum = rightMin < minimum ? rightMin : minimum;
        }
    }
    return minimum;
}

/* Find the maximum element in a tree node*/
int BinaryTree::max(TreeNode *node)
{

    if (node == nullptr)
        throw new EmptyTreeException;
    auto maximum = node->data;
    if (!node->isLeaf())
    {
        if (node->left != nullptr)
        {
            auto leftMax = max(node->left);
            maximum = leftMax < maximum ? leftMax : maximum;
        }
        if (node->right != nullptr)
        {
            auto rightMax = max(node->right);
            maximum = rightMax < maximum ? rightMax : maximum;
        }
    }
    return maximum;
}

/* Get the height of a tree, from the specified node (usually root),
which is the number of edges from the root node to the deepest leaf
node. */
int BinaryTree::getHeight(TreeNode *node)
{
    auto height = 0;
    if (node != nullptr)
    {
        if (!node->isLeaf())
        {
            int leftHeight = 0, rightHeight = 0;
            if (node->left != nullptr)
                leftHeight = getHeight(node->left);
            if (node->right != nullptr)
                rightHeight = getHeight(node->right);
            height = leftHeight > rightHeight ? leftHeight : rightHeight;
            height++;
        }
    }
    return height;
}

void BinaryTree::insert(int t_data)
{
    insert(t_data, this->root);
    this->size++;
}

void BinaryTree::insert(int t_data, TreeNode *node)
{
    if (node != nullptr)
    {
        if (t_data <= node->data)
        {
            if (node->left == nullptr)
                node->left = new TreeNode(t_data);
            else
                insert(t_data, node->left);
        }
        else
        {
            if (node->right == nullptr)
                node->right = new TreeNode(t_data);
            else
                insert(t_data, node->right);
        }
    }
    else
    {
        if (this->root == nullptr)
        {
            this->root = new TreeNode(t_data);
        }
        else
        {
            // Shouldn't encounter a null node unless it's the root.
            throw new std::exception;
        }
    }
}

bool BinaryTree::contains(int t_data) { return in(t_data, this->root); }

bool BinaryTree::in(int t_data, TreeNode *node)
{
    bool found = false;
    if (node != nullptr)
    {
        if (t_data == node->data)
            found = true;
        else if (t_data <= node->data)
            found = in(t_data, node->left);
        else
            found = in(t_data, node->right);
    }
    return found;
}

/* A full binary tree is a binary tree in which every node has either
zero or two children. That is, no nodes have only one child. */
bool BinaryTree::fullTree() { return isFull(this->root); }

bool BinaryTree::isFull(TreeNode *node)
{
    auto result = true;
    if (node == nullptr)
        throw new EmptyTreeException;
    if (!node->isLeaf())
    {
        if (!node->hasBoth())
        {
            result = false;
        }
        else
        {
            isFull(node->left);
            isFull(node->right);
        }
    }
    return result;
}

void BinaryTree::inOrderPrint(TreeNode *node)
{
    if (node != nullptr)
    {
        inOrderPrint(node->left);
        std::cout << node->data;
        inOrderPrint(node->right);
    }
}

void BinaryTree::preOrderPrint(TreeNode *node)
{
    if (node != nullptr)
    {
        std::cout << node->data;
        preOrderPrint(node->left);
        preOrderPrint(node->right);
    }
}

void BinaryTree::postOrderPrint(TreeNode *node)
{
    if (node != nullptr)
    {
        postOrderPrint(node->left);
        postOrderPrint(node->right);
        std::cout << node->data;
    }
}

void BinaryTree::printInOrder() { inOrderPrint(this->root); }
void BinaryTree::printPreOrder() { preOrderPrint(this->root); }
void BinaryTree::printPostOrder() { postOrderPrint(this->root); }

/*-------------------------------BINARY TREE---------------------------------*/

void BinarySearchTree::insert(int t_data)
{
    BinaryTree::insert(t_data);
    this->balanceTree();
}

int BinarySearchTree::min(TreeNode *node)
{
    if (node == nullptr) throw new EmptyTreeException;
    if (node->left != nullptr) return this->min(node->left);
    else {return node->data; }
}

int BinarySearchTree::max(TreeNode *node)
{
    if (node == nullptr) throw new EmptyTreeException;
    if (node->right != nullptr) return this->max(node->right);
    else {return node->data; }
}

void BinarySearchTree::balanceTree() {}
