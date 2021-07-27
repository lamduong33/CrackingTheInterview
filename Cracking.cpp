#include <exception>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/*
** author: Lam Duong
** Cracking the coding interview problems and solutions.
*/
class Cracking
{
public:
    /*
    ** 1.4) Palindrome Permutation:
    ** ----------------------------------------------------------------------
    ** Given a string, write a function to check if it is a permutation of a
    ** palindrome. A palindrome is a word or phrase that is the same forward and
    ** backwards. A permutation is a rearrangement of letters. The palindrome
    ** does not need to be limited to just dictionary words.
    **
    ** Input: Tact Coa
    ** Output: true (pertmutations: "taco cat", "atco cta", etc.)
    */
    static bool palindromePermutation(const std::string &str)
    {
        auto result = false;
        auto charCount = 0;
        for (int i = 0; i < str.length(); i++)
            if (str.at(i) != ' ')
                charCount++;
        std::unordered_set<char> occursOnce;

        // O(n)
        for (int i = 0; i < str.length(); i++)
        {
            char c = std::tolower(str.at(i));
            if (c == ' ')
                continue;
            if (!occursOnce.count(c))
                occursOnce.insert(c);
            else
                occursOnce.erase(c);
        }

        if (((charCount % 2 == 0) && (occursOnce.empty())) ||
            ((charCount % 2 == 1) && (occursOnce.size() == 1)))
            result = true;

        return result;
    }

    /*
    ** 1.5) One Away:
    ** ----------------------------------------------------------------------
    ** There are three types of edits that can be performed on strings: insert a
    ** character, remove a character, or replace a character. Given two strings,
    ** write a function to check if they are one edit (or zero edits away).
    ** e.g. pale, ple -> true
    */
    static bool oneAway(const std::string &str1, const std::string &str2)
    {
        auto result = false;
        auto smaller = str1.length() < str2.length() ? str1 : str2;
        auto bigger = str1.length() < str2.length() ? str2 : str1;
        int mismatchCount = 0, i = 0, j = 0;
        int difference = bigger.length() - smaller.length();

        while (i < smaller.length() && j < bigger.length())
        {
            if (bigger.at(j) != smaller.at(i))
            {
                mismatchCount++;
                if (difference == 0)
                    i++;
            }
            else
            {
                i++;
            }
            j++;
        }

        if (mismatchCount <= 1)
            result = true;
        return result;
    }

    /*
    ** 1.6) String Compression: Implement a method to perform basic string
    compression using the counts of repeated characters. For example, the string
    aabcccccaaa would become a2b1c5a3. If the "compressed" string wouldn ot
    become samller than the original string, your method shoudl return the
    original string. The input is only uppercase and lowecase letters (a-z).
     */
    static std::string stringCompression(const std::string &str)
    {
        std::string result;
        int charCount = 0;
        char c = '\0';
        // std::unordered_map<char, int> charCounts;
        for (int i = 0; i < str.length(); i++)
        {
            if (str.at(i) != c)
            {
                if (i != 0)
                    result += c + std::to_string(charCount);
                c = str.at(i);
                charCount = 0;
            }
            charCount++;
        }
        result += c + std::to_string(charCount);
        result = result.length() <= str.length() ? result : str;
        return result;
    }

    /*
    ** 1.7) Rotate Matrix:
    **
    ** ----------------------------------------------------------------------
    ** Given an image represented by an NxN matrix, where each pixel in the
    ** image is 4 bytes, write a method to rotate the image by 90 degrees. Can
    ** you do this in place?
    */
    static void rotateMatrix(std::vector<std::vector<int>> &matrix)
    {
        int N = matrix.size();
        // O(N/2 * N) = O(N^2)
        for (int rowIndex = 0; rowIndex < N / 2; rowIndex++)
        {
            for (int columnIndex = rowIndex; columnIndex < N - 1 - rowIndex;
                 columnIndex++)
            {
                auto top = matrix[rowIndex][columnIndex];
                auto right = matrix[columnIndex][N - 1 - rowIndex];
                auto bottom = matrix[N - 1 - rowIndex][N - 1 - columnIndex];
                auto left = matrix[N - 1 - columnIndex][rowIndex];

                matrix[rowIndex][columnIndex] = left;                  // top
                matrix[columnIndex][N - 1 - rowIndex] = top;           // right
                matrix[N - 1 - rowIndex][N - 1 - columnIndex] = right; // bottom
                matrix[N - 1 - columnIndex][rowIndex] = bottom;        // left
            }
        }
    }

    /*
    ** 1.8) Zero Matrix
    **
    ---------------------------------------------------------------------------
    ** Write an algorithm such that if an element in an MxN matrix is 0, its
    entire row and column are set to 0.*/
    static void zeroMatrix(std::vector<std::vector<int>> &matrix)
    {
        int M = matrix.size();    // row
        int N = matrix[0].size(); // column
        std::vector<int> emptyRow(N, 0);
        auto indices = zeroIndices(matrix); // Find the indices of zeros (M*N)

        for (auto &rowIndex : indices.first)
        {
            matrix[rowIndex] = emptyRow;
        }
        for (auto &columnIndex : indices.second)
        {
            for (int i = 0; i < M; i++)
            {
                matrix[i][columnIndex] = 0;
            }
        }
    }

    /*
    ** 1.9) String Rotation
    **
    ---------------------------------------------------------------------------
    ** Assume you have a method isSubstring which checks if one word is a
    ** substring of another. Given two strings, s1 and s2, write code to check if
    ** s2 is a rotation of s1 using only one call to isSubstring(e.g.
    ** "waterbottle" is a rotation of "erbottlewat").
    NOTE: A rotation is simply where a chunk is moved around, in the case of
    "waterbottle", "wat" is moved to the end of the string, creating
    "erbottlewat"
    */
    static bool stringRotation(const std::string &substr, const std::string &str)
    {
        return isSubstring(substr, str + str);
    }

    /* Helper Method to see if a string is a substring of another. */
    static bool isSubstring(const std::string &substr, const std::string &str)
    {
        bool result = false;
        auto substringIndex = 0;
        for (int i = 0; i < str.length(); i++)
        {
            if (str.at(i) == substr.at(substringIndex))
            {
                if (substringIndex == substr.length() - 1)
                {
                    result = true;
                    break;
                }
                substringIndex++;
            }
            else
            {
                substringIndex = 0;
            }
        }
        return result;
    }

    /* Helper function for finding zeros within an MxN matrix. The first item in
    the pair is the row index and the second item is column index.*/
    static std::pair<std::unordered_set<int>, std::unordered_set<int>>
    const zeroIndices(std::vector<std::vector<int>> &matrix)
    {
        std::unordered_set<int> rowIndices;
        std::unordered_set<int> columnIndices;
        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix.size(); j++)
            {
                if (matrix[i][j] == 0)
                {
                    rowIndices.insert(i);
                    columnIndices.insert(j);
                }
            }
        }
        std::pair<std::unordered_set<int>, std::unordered_set<int>> result(
            rowIndices, columnIndices);
        return result;
    }

    /* Helper function to print out a matrix for simple debugging */
    static void printMatrix(std::vector<std::vector<int>> &matrix)
    {
        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[i].size(); j++)
            {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    /* Class for a simple linked list */
    struct Node
    {
        Node *next = nullptr;
        Node *previous = nullptr;
        int data;

        Node(int t_data) : data{t_data} {}
        Node(std::vector<int> &list)
        {
            auto it = this;
            it->data = list[0];
            for (int i = 1; i < list.size(); i++)
            {
                it->next = new Node(list[i]);
                it->next->previous = it;
                it = it->next;
            }
        }

        /* Traverse the list and append to the end.*/
        void appendToTail(int t_data)
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

        void joinList(Node *anotherList)
        {
            auto n = this;
            while (n->next != nullptr)
            {
                n = n->next;
            }
            n->next = anotherList;
            anotherList->previous = n;
        }

        Node *deleteNode(Node *t_head, int t_data)
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

        void printList()
        {
            auto it = this;
            while (it != nullptr)
            {
                std::cout << it->data;
                it = it->next;
            }
        }
    };

    /*
    ** 2.1) Remove Dups:
    **
    ** -----------------------------------------------------------------
    ** Write code to remove duplicates from an unsorted linked list.
    */
    static void removeDups(Node *list)
    {
        std::unordered_set<int> duplicates;
        std::unordered_set<int> encountered;
        auto it = list;
        Node *previous;

        // Find duplicates
        while (it != nullptr)
        {
            if (encountered.count(it->data))
            {
                previous->next = it->next;
            }
            else
            {
                encountered.insert(it->data);
                previous = it;
            }
            it = it->next;
        }
    }

    /*
    ** 2.2) Return Kth to Last:
    **
    ** ----------------------------------------------------------------------
    ** Implement an algorithm to find the kth to last last element of a singly
    ** linked list.
    */
    static Node *kthToLast(int k, Node *list)
    {
        Node *result;
        auto size = 0;
        auto count = 0;
        auto it = list;
        auto previous = it;

        // Find the size
        while (it != nullptr)
        {
            size++;
            it = it->next;
        }
        if ((k > size) || (k < 1))
            throw std::logic_error("k has to be 1 < k < size");
        it = list;

        // Remove the item
        while (it != nullptr)
        {
            if (count == size - k)
            {
                result = it;
                break;
            }
            else
            {
                previous = it;
            }
            count++;
            it = it->next;
        }
        return result;
    }

    /*
    ** 2.3) Delete Middle Node:
    ** ----------------------------------------------------------------------
    ** Implement an algorithm to delete a node in the middle (.e., any node but
    ** the first and last node, not necessarily the exact middle) of a singly
    ** linked list, given only access to that node.
    **
    ** Input: the node c from the linked list a->b->c->d->e->f
    ** Result: nothing is returned, but the new linked list looks like
    ** a->b->d->e->f
    */
    static void deleteMiddleNode(Node *c)
    {
        // This is assuming that the function is never used on the last element
        // or the first element
        c->data = c->next->data;
        c->next = c->next->next;
    }

    /*
    ** 2.4) Partition:
    ** ----------------------------------------------------------------------
    ** Write code to partition a linked list around a value x, such that all
    ** nodes less than x come before all nodes greater than or equal to x. IF x
    ** is contained within the list, the values of x only need to be after the
    ** elements less than x (see below). The partition element x can appear
    ** anywhere in the right partitions.
    **
    ** Input:  3 -> 5 -> 8 -> 5 -> 10 -> 2 -> 1 [partition = 5]
    ** Output: 3 -> 1 -> 2 -> 10 -> 5 -> 5 -> 8
    */
    static Node *partition(Node *t_list, int x)
    {
        auto node = t_list;
        Node *previous = nullptr;
        while (node != nullptr)
        {
            // Move to the beginning
            if ((node->data < x) && (previous != nullptr))
            {
                previous->next = node->next;
                node->next = t_list;
                t_list->previous = node;
                t_list = node;
                node = previous->next;
            }
            else
            {
                previous = node;
                node = node->next;
            }
        }
        return t_list;
    }

    /*
    ** 2.5) Sum Lists:
    ** ----------------------------------------------------------------------
    ** You have two numbers represented by a linked list, where
    ** each node contains a single digit. The digits are stored in reverse order,
    ** such that the 1-s digit is at the head of the list. Write a function that
    ** adds the two numbers and returns the sum as a linked list.
    **
    ** Input: (7 -> 1 -> 6) + (5-> 9 -> 2), that is, 617 + 295
    ** Output: (2 -> 1 -> 9), that is, 912
    **
    ** Follow up: Suppose the digits are stored in forward order, repeat the
    ** above problem.
    */
    static Node *sumLists(Node *list1, Node *list2)
    {
        if ((list1 == nullptr) && (list2 == nullptr))
            return nullptr;
        if ((list1 != nullptr) && (list2 == nullptr))
            return list1;
        if ((list1 == nullptr) && (list2 != nullptr))
            return list2;

        bool carry = false;
        bool first = true;
        Node *result;
        Node *head;

        // O(m + n)
        while ((list1 != nullptr) && (list2 != nullptr))
        {
            auto addition = list1->data + list2->data + carry;

            if (addition >= 10)
            {
                carry = true;
                addition -= 10;
            }
            else
            {
                carry = false;
            }

            if (first)
            {
                result = new Node(addition);
                head = result;
                first = false;
            }
            else
            {
                head->next = new Node(addition);
                head = head->next;
            }

            // Advance
            list1 = list1->next;
            list2 = list2->next;
        }

        // Take care of leftovers
        Node *leftOver;
        if (list1 != nullptr || list2 != nullptr)
        {
            leftOver = (list1 == nullptr) ? list2 : list1;
            auto head = leftOver;
            while (carry == true)
            {
                if (head != nullptr)
                {
                    head->data++;
                    if (head->data >= 10)
                        head->data -= 10;
                    else
                        break;
                }
                else
                {
                    head->appendToTail(1);
                    break;
                }
                head = head->next;
            }
            result->joinList(leftOver);
        }
        else if (carry == true)
        {
            result->appendToTail(1);
        }
        return result;
    }

    /*
    ** 2.6) Palindrome:
    ** ----------------------------------------------------------------------
    ** Implement a function to check if a linked list is a
    ** palindrome.
    ** 1 2 3 4 5 4 3 2 1 -> true
    ** 1 2 3 2 1 2 -> false
    */
    static bool palindrome(Node *t_list)
    {
        auto result = true;
        std::vector<int> vector;

        // Turn this into a vector. O(n)
        auto head = t_list;
        while (head != nullptr)
        {
            vector.push_back(head->data);
            head = head->next;
        }

        // Detect palindrome from the vector
        for (int i = 0; i <= ((int)vector.size()/2); i++)
        {
            // 0 1 2 3 4
            if (vector[i] != vector[vector.size()-(i+1)])
            {
                result = false;
                break;
            }
        }

        return result;
    }

    /*
    ** 2.7) Intersection:
    ** ----------------------------------------------------------------------
    ** Given two (singly) linked lists, determine if the two lists intersect.
    ** Return the intersecting node. Not that the intersection is defined based
    ** reference, not value. That is, the kth node of the first linked list is
    ** the exact same node (by reference) as the jth node of the second linked
    ** list, then they are intersecting.
    */

    /*
    ** 2.8) Loop Detection:
    ----------------------------------------------------------------------
    Given a circular linked list, implement an algorithm that returns the node
    at the beginning of the loop. A circular linked list is a (corrupt) linked
    list in which a node's next pointer points to an earlier node, so as to make
    a loop in the linked list.
    Input: A -> B -> C -> D -> E -> C [the same C as earlier]
    Output: C
     */
};

int main(int argc, char *argv[])
{
    std::vector<int> a = {1, 2, 1};
    Cracking::Node list1(a);
    std::cout << Cracking::palindrome(&list1);
    return 0;
}
