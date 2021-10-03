#include "DataStructures.hpp"

/*-------------------------------BINARY TREE---------------------------------*/

size_t DataStructures::BinaryTree::getSize() { return this->size; }

DataStructures::BinaryTree::TreeNode* DataStructures::BinaryTree::getRoot()
{
    return this->root;
}

bool DataStructures::BinaryTree::validTree() { return isValid(this->root); }

bool DataStructures::BinaryTree::isValid(TreeNode* node)
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

int DataStructures::BinaryTree::min(TreeNode* node)
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

int DataStructures::BinaryTree::max(TreeNode* node)
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

int DataStructures::BinaryTree::getHeight(TreeNode* node)
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

void DataStructures::BinaryTree::insert(int t_data)
{
    insert(t_data, this->root);
    this->size++;
}

void DataStructures::BinaryTree::insert(int t_data, TreeNode* node)
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

bool DataStructures::BinaryTree::fullTree() { return isFull(this->root); }

bool DataStructures::BinaryTree::isFull(TreeNode* node)
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

void DataStructures::BinaryTree::inOrderPrint(TreeNode* node)
{
    if (node != nullptr)
    {
        inOrderPrint(node->left);
        std::cout << node->data;
        inOrderPrint(node->right);
    }
}

void DataStructures::BinaryTree::preOrderPrint(TreeNode* node)
{
    if (node != nullptr)
    {
        std::cout << node->data;
        preOrderPrint(node->left);
        preOrderPrint(node->right);
    }
}

void DataStructures::BinaryTree::postOrderPrint(TreeNode* node)
{
    if (node != nullptr)
    {
        postOrderPrint(node->left);
        postOrderPrint(node->right);
        std::cout << node->data;
    }
}

void DataStructures::BinaryTree::printInOrder() { inOrderPrint(this->root); }
void DataStructures::BinaryTree::printPreOrder() { preOrderPrint(this->root); }
void DataStructures::BinaryTree::printPostOrder()
{
    postOrderPrint(this->root);
}
