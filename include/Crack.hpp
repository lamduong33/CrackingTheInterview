#ifndef CRACK_HPP
#define CRACK_HPP

#include "../include/DataStructures.hpp"
#include <exception>
#include <iostream>
#include <list>
#include <memory> // Smart pointers
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace DataStructures;

bool palindromePermutation(const std::string&);
bool oneAway(const std::string& str1, const std::string& str2);
std::string stringCompression(const std::string& str);
void rotateMatrix(std::vector<std::vector<int>>& matrix);
void zeroMatrix(std::vector<std::vector<int>>& matrix);
std::pair<std::unordered_set<int>, std::unordered_set<int>> const
zeroIndices(std::vector<std::vector<int>> const& matrix);
bool stringRotation(const std::string& substr, const std::string& str);
bool isSubstring(const std::string& substr, const std::string& str);
void printMatrix(std::vector<std::vector<int>>& matrix);

void removeDups(DoublyLinkedNode* list);
DoublyLinkedNode* kthToLast(int k, DoublyLinkedNode* list);
void deleteMiddleNode(DoublyLinkedNode* c);
DoublyLinkedNode* partition(DoublyLinkedNode* t_list, int x);
DoublyLinkedNode* sumLists(DoublyLinkedNode* list1, DoublyLinkedNode* list2);
bool palindrome(DoublyLinkedNode* t_list);
bool intersection(DoublyLinkedNode* list1, DoublyLinkedNode* list2);
DoublyLinkedNode* loopDetection(DoublyLinkedNode* list);
DoublyLinkedNode* reverseSinglyLinkedList(DoublyLinkedNode* list);
void split(DoublyLinkedNode* list, DoublyLinkedNode** left,
           DoublyLinkedNode** right);
DoublyLinkedNode* mergeSorted(DoublyLinkedNode* left, DoublyLinkedNode* right);
void mergeSortLinkedList(DoublyLinkedNode** list);


void sortStack(Stack& t_stack);


bool routeBetweenNodes(Node* origin, Node* destination);
TreeNode* minimalTreeRecurse(int begin, int end, std::vector<int>& array);
std::vector<std::list<TreeNode*>> listOfDepths(TreeNode* root);
bool checkBalanced(TreeNode* root);
bool recursiveDFS(TreeNode* root, std::list<TreeNode*> nodesList,
                  std::list<bool> directionsList);

#endif // CRACK_HPP
