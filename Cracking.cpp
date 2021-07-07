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
        auto width = N;
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
    zeroIndices(std::vector<std::vector<int>> &matrix)
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

    /*
    ** Linked List for easier working with linked list compared to std::list.
     */
    class LinkedList
    {
    public:
        class Node
        {
        public:
            int data;
            Node *next;
            Node() : data{0}, next{nullptr} {}
            Node(int t_data) : data{t_data}, next{nullptr} {}
            Node(int t_data, Node *t_next) : data{t_data}, next{t_next} {}
            bool hasNext() { return this->next != nullptr;}
            void addNode(Node *newNode) { this->next = newNode; }
            void setData(int t_data) { this->data = t_data;}
            void setNext(Node *newNode) { this->next = newNode; }

            Node *addNode(int element)
            {
                auto newNode = new Node(element);
                this->next = newNode;
                return newNode;
            }
            Node* deleteNode(Node* head, int element)
            {
                Node* it = head;
                if (it->data == element)
                {
                    return it->next;
                }
                while (it->next != nullptr)
                {
                    if(it->data == element)
                    {
                        it->next = it->next->next;
                        break;
                    }
                    it = it->next;
                }
                return head;
            }
        };
        Node *head;
        Node *tail;
        int size;

        /* Standard constructor */
        LinkedList()
        {
            this->tail = new Node();
            this->head = tail;
        }

        /* Constructor for turning an STL vector in to a custom Linked List*/
        LinkedList(std::vector<int> t_array)
        {
            this->head = new Node();
            auto it = head;
            for (int i = 0; i < t_array.size(); i++)
            {
                if (i == 0)
                {
                    it->setData(t_array[i]);
                    this->tail = it;
                    continue;
                }
                auto newNode = new Node(t_array[i]);
                it->addNode(newNode);
                this->tail = newNode;
                it = it->next;
            }
        }

        Node *getHead() { return this->head; }
        Node *getTail() { return this->tail; }
        void setHead(Node* newHead) { this->head = newHead;}
        void setTail(Node* newTail) { this->tail = newTail;}

        void push_back(int element)
        {
            this->tail = this->tail->addNode(element);
        }
        void push_front(int element)
        {
            this->head = this->head->addNode(element);
        }
        void printList()
        {
            auto node = this->head;
            while (node != nullptr)
            {
                std::cout << node->data;
                node = node->next;
            }
        }
    };

    /*
    ** 2.1) Remove Dups:
    **
    ** -----------------------------------------------------------------
    ** Write code to remove duplicates from an unsorted linked list.
    */
    static void removeDups(LinkedList &list)
    {
        std::unordered_set<int> duplicates;
        std::unordered_set<int> encountered;
        auto it = list.getHead();
        LinkedList::Node* previous;

        // Find duplicates
        while(it != nullptr)
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

    /*How would you solve this problem if a temporary buffer is not allowed?*/
    static void removeDupsV2(std::list<int> &list) {}
};

int main(int argc, char *argv[])
{
    std::vector<int> a = {4,5,3,1,5};
    Cracking::LinkedList list(a);
    Cracking::removeDups(list);
    list.printList();
    return 0;
}
