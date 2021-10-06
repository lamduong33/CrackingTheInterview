#include "../include/DataStructures.hpp"

using namespace DataStructures;

/*-------------------------------LINKED LIST---------------------------------*/

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

void Node::joinList(Node* anotherList)
{
    auto n = this;
    while (n->next != nullptr)
    {
        n = n->next;
    }
    n->next = anotherList;
    anotherList->previous = n;
}

Node* Node::deleteNode(Node* t_head, int t_data)
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
int Stack::pop()
{
    if (top == nullptr) throw new EmptyStackException;
    int item = top->getData();
    top = top->getNext();
    size--;
    return item;
}

void Stack::push(int item)
{
    auto t = new StackNode(item);
    t->setNext(top);
    top = t;
    size++;
}

int Stack::peek()
{
    if (top == nullptr) throw new EmptyStackException;
    return top->getData();
}

bool Stack::isEmpty() { return (size == 0); }
void Stack::printStack()
{
    auto head = top;
    for (auto i = 0; i < size; i++)
    {
        std::cout << head->getData();
        if (i != size - 1) std::cout << "->";
        head = head->getNext();
    }
    std::cout << std::endl;
}

/*-------------------------------QUEUE---------------------------------------*/
template <class T> void Queue<T>::add(T item)
{
    auto t = new QueueNode(item);
    if (last != nullptr) last->next = t;
    last = t;
    if (first == nullptr) first = last;
}

template <class T> T Queue<T>::remove()
{
    if (first == nullptr) throw new NoSuchElementException;
    T data = first->data;
    first = first->next;
    if (first == nullptr)
    {
        delete (last);
        last = nullptr;
    }
    return data;
}

template <class T> T Queue<T>::peek()
{
    if (first == nullptr) throw new NoSuchElementException;
    return first->data;
}

template <class T> bool Queue<T>::isEmpty() { return first == nullptr; }

/*-------------------------------BINARY TREE---------------------------------*/

size_t BinaryTree::getSize() { return this->size; }

BinaryTree::TreeNode* BinaryTree::getRoot() { return this->root; }

bool BinaryTree::validTree() { return isValid(this->root); }

bool BinaryTree::isValid(TreeNode* node)
{
    auto result = true;
    if (node == nullptr) return result;
    if (node->isLeaf()) return result;
    if (node->left != nullptr && (max(node->left) > node->data))
    {
        result = false;
    }
    if (result && node->right != nullptr && (min(node->right) < node->data))
    {
        result = false;
    }
    if (!isValid(node->left) || !isValid(node->right)) result = false;
    return result;
}

int BinaryTree::min(TreeNode* node)
{
    if (node == nullptr) throw new EmptyTreeException;
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

int BinaryTree::max(TreeNode* node)
{

    if (node == nullptr) throw new EmptyTreeException;
    auto maximum = node->data;
    if (!node->isLeaf())
    {
        if (node->left != nullptr)
        {
            auto leftMin = min(node->left);
            maximum = leftMin < maximum ? leftMin : maximum;
        }
        if (node->right != nullptr)
        {
            auto rightMin = min(node->right);
            maximum = rightMin < maximum ? rightMin : maximum;
        }
    }
    return maximum;
}

int BinaryTree::getHeight(TreeNode* node)
{
    auto height = 0;
    if (node != nullptr)
    {
        if (!node->isLeaf())
        {
            int leftHeight = 0, rightHeight = 0;
            if (node->left != nullptr) leftHeight = getHeight(node->left);
            if (node->right != nullptr) rightHeight = getHeight(node->right);
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

void BinaryTree::insert(int t_data, TreeNode* node)
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


bool BinaryTree::fullTree() { return isFull(this->root); }

bool BinaryTree::isFull(TreeNode* node)
{
    auto result = true;
    if (node == nullptr) throw new EmptyTreeException;
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

void BinaryTree::inOrderPrint(TreeNode* node)
{
    if (node != nullptr)
    {
        inOrderPrint(node->left);
        std::cout << node->data;
        inOrderPrint(node->right);
    }
}

void BinaryTree::preOrderPrint(TreeNode* node)
{
    if (node != nullptr)
    {
        std::cout << node->data;
        preOrderPrint(node->left);
        preOrderPrint(node->right);
    }
}

void BinaryTree::postOrderPrint(TreeNode* node)
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

void BinarySearchTree::balanceTree()
{
    // if (not balanced())
    // {

    // }
}
