#include <climits>
#include <exception>
#include <iostream>
#include <list>
#include <memory> // For pointers
#include <stack>
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
        for (int i = 0; i < (int)str.length(); i++)
            if (str.at(i) != ' ')
                charCount++;
        std::unordered_set<char> occursOnce;

        // O(n)
        for (int i = 0; i < (int)str.length(); i++)
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

        while (i < (int)smaller.length() && j < (int)bigger.length())
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
        for (int i = 0; i < (int)str.length(); i++)
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
    ** substring of another. Given two strings, s1 and s2, write code to check
    if
    ** s2 is a rotation of s1 using only one call to isSubstring(e.g.
    ** "waterbottle" is a rotation of "erbottlewat").
    NOTE: A rotation is simply where a chunk is moved around, in the case of
    "waterbottle", "wat" is moved to the end of the string, creating
    "erbottlewat"
    */
    static bool stringRotation(const std::string &substr,
                               const std::string &str)
    {
        return isSubstring(substr, str + str);
    }

    /* Helper Method to see if a string is a substring of another. */
    static bool isSubstring(const std::string &substr, const std::string &str)
    {
        bool result = false;
        auto substringIndex = 0;
        for (int i = 0; i < (int)str.length(); i++)
        {
            if (str.at(i) == substr.at(substringIndex))
            {
                if (substringIndex == (int)substr.length() - 1)
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
    static std::pair<std::unordered_set<int>, std::unordered_set<int>> const
    zeroIndices(std::vector<std::vector<int>> const &matrix)
    {
        std::unordered_set<int> rowIndices;
        std::unordered_set<int> columnIndices;
        for (int i = 0; i < (int)matrix.size(); i++)
        {
            for (int j = 0; j < (int)matrix.size(); j++)
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
        for (int i = 0; i < (int)matrix.size(); i++)
        {
            for (int j = 0; j < (int)matrix[i].size(); j++)
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

        explicit Node(int t_data) : data{t_data} {}
        explicit Node(std::vector<int> &list) : data{list[0]}
        {
            auto it = this;
            for (int i = 1; i < (int)list.size(); i++)
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
        Node *result = nullptr;
        auto size = 0;
        auto count = 0;
        auto it = list;

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
    ** each node contains a single digit. The digits are stored in reverse
    *order,
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
        if (list1 != nullptr || list2 != nullptr)
        {
            auto leftOver = (list1 == nullptr) ? list2 : list1;
            auto temp = leftOver;
            while (carry == true)
            {
                if (temp != nullptr)
                {
                    temp->data++;
                    if (temp->data >= 10)
                        temp->data -= 10;
                    else
                        break;
                }
                else
                {
                    temp->appendToTail(1);
                    break;
                }
                temp = temp->next;
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
        std::stack<int> stack;

        auto turtle = t_list;
        auto hare = t_list;
        while (hare != nullptr && hare != hare->next)
        {
            stack.push(turtle->data);
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
    static bool intersection(Node *list1, Node *list2)
    {
        auto result = false;
        // Create a hashed set of old values
        std::unordered_set<Node *>
            encounteredNodes; // list of nodes in 1st node
        auto head1 = list1;
        auto head2 = list2;

        while (head1 != nullptr)
        {
            if (encounteredNodes.count(head1))
            {
                break; // circular loop detected, break
            }
            else
            {
                encounteredNodes.insert(head1);
            }
            head1 = head1->next;
        }

        while (head2 != nullptr)
        {
            if (encounteredNodes.count(head2))
            {
                result = true;
                break;
            }
            head2 = head2->next;
        }

        return result;
    }

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
    static Node *loopDetection(Node *list)
    {
        Node *result = nullptr;
        std::unordered_set<Node *> nodesSet;
        auto head = list;

        while (head != nullptr)
        {
            if (nodesSet.count(head))
            {
                result = head;
                break;
            }
            else
            {
                nodesSet.insert(head);
            }
            head = head->next;
        }
        return result;
    }

    static Node *reverseSinglyLinkedList(Node *list)
    {
        Node *head = nullptr;
        while (list != nullptr)
        {
            auto newNode = new Node(list->data);
            newNode->next = head;
            head = newNode;
            list = list->next;
        }
        return head;
    }

    // Merge sort for Linked List
    static void mergeSortLinkedList(Node **list)
    {
        Node *head = *list;
        Node *left;
        Node *right;

        if ((head == nullptr) || (head->next == nullptr))
            return;
        split(head, &left, &right);
        mergeSortLinkedList(&left);
        mergeSortLinkedList(&right);

        *list = mergeSorted(left, right);
    }

    /* Merge sorted lists for sor */
    static Node *mergeSorted(Node *left, Node *right)
    {
        Node *result = nullptr;
        if (left == nullptr)
            return right;
        else if (right == nullptr)
            return left;

        if (left->data <= right->data)
        {
            result = left;
            result->next = mergeSorted(left->next, right);
        }
        else
        {
            result = right;
            result->next = mergeSorted(left, right->next);
        }
        return result;
    }

    static void split(Node *list, Node **left, Node **right)
    {
        auto turtle = list;
        auto hare = list->next;

        while (hare != nullptr)
        {
            hare = hare->next;
            if (hare != nullptr)
            {
                turtle = turtle->next;
                hare = hare->next;
            }
        }
        *left = list;
        *right = turtle->next;
        turtle->next = nullptr;
    }

    // ==============================Chapter 3===============================

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

        int pop()
        {
            if (top == nullptr)
                throw new EmptyStackException;
            int item = top->getData();
            top = top->getNext();
            size--;
            return item;
        }

        void push(int item)
        {
            auto t = new StackNode(item);
            t->setNext(top);
            top = t;
            size++;
        }

        int peek()
        {
            if (top == nullptr)
                throw new EmptyStackException;
            return top->getData();
        }

        bool isEmpty() { return (size == 0); }

        void printStack()
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
    };

    /* The queue class is FIFO (first in first out) */
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
        class NoSuchElementException : public std::exception
        {
            virtual const char *what() const throw()
            {
                return "No such element in queue!";
            }
        };

        void add(T item)
        {
            auto t = new QueueNode(item);
            if (last != nullptr)
                last->next = t;
            last = t;
            if (first == nullptr)
                first = last;
        }

        T remove()
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

        T peek()
        {
            if (first == nullptr)
                throw new NoSuchElementException;
            return first->data;
        }

        bool isEmpty() { return first == nullptr; }
    };

    /*
    ** 3.2) Stack Min:
    ** ----------------------------------------------------------------------
    ** How would you design a stack which, in addition to push and pop, has a
    ** function min which returns the minimum element? Push, pop, and min should
    ** all operate in O(1) time.
    */

    class StackMin : public Stack
    {
    public:
        StackNode *minimumStack; // keeping track of all minimum elements
        int pop()
        {
            if (top == nullptr)
                throw new EmptyStackException;
            if (top->getData() == minimumStack->getData())
            {
                minimumStack = minimumStack->getNext();
            }
            int item = top->getData();
            top = top->getNext();
            return item;
        }

        void push(int t_data)
        {
            if (t_data < minimumStack->getData())
            {
                auto newMinimum = new StackNode(t_data);
                newMinimum->setNext(minimumStack);
                minimumStack = newMinimum;
            }
            auto newNode = new StackNode(t_data);
            newNode->setNext(top);
            top = newNode;
        }

        int min() { return this->minimumStack->getData(); }
    };

    /*
    ** 3.3) Stack of Plates:
    ** ----------------------------------------------------------------------
    ** Stack of Plates: Imagine a (literal) stack of plates. If the stack gets
    ** too high, it might topple. Therefore, in real life, we would likely start
    ** a new stack when the previous stack exceeds some threshold. Implement a
    ** data structure SetOfStacks that mimics this. SetOfStacks should be
    ** composed of several stacks and should create a new stack once the
    *previous
    ** one exceeds capacity. SetOfStacks. push() and SetOfStacks. pop() should
    ** behave identically to a single stack (that is, pop () should return the
    ** same values as it would if there were just a single stack).
    **
    ** FOLLOW UP: Implement a function popAt ( int index) which performs a pop
    ** operation on a specific sub-stack.
    */

    class SetOfStacks
    {

        std::vector<Stack> m_setOfStacks;
        std::vector<int> m_stackSizes;
        int m_maxStackSize;
        Stack *lastStack;
        int lastStackSize;

        void createNewStack()
        {
            m_setOfStacks.push_back(*(new Stack()));
            m_stackSizes.push_back(0);
            getLastStack();
        }

        void removeLastStack()
        {
            // delete &lastStack;
            m_setOfStacks.pop_back();
            m_stackSizes.pop_back();
            getLastStack();
        }

        void getLastStack()
        {
            lastStack = &m_setOfStacks[m_setOfStacks.size() - 1];
            lastStackSize = m_stackSizes[m_stackSizes.size() - 1];
        }

    public:
        // Start out with one empty stack
        SetOfStacks()
        {
            m_maxStackSize = 20;
            m_setOfStacks.push_back(*(new Stack()));
            m_stackSizes.push_back(0);
            getLastStack();
        }

        void push(int t_item)
        {
            if (lastStackSize == m_maxStackSize)
                createNewStack();
            lastStack->push(t_item);
            lastStackSize++;
        }

        int pop()
        {
            auto result = lastStack->pop();
            lastStackSize--;
            if (lastStackSize == 0)
                removeLastStack();
            return result;
        }

        void printStacks()
        {
            for (int i = 0; i < (int)m_setOfStacks.size(); i++)
            {
                std::cout << "Stack " << i << ": ";
                m_setOfStacks[i].printStack();
            }
        }
    };

    /*
    ** 3.4) Queue of Stacks:
    ** ----------------------------------------------------------------------
    ** Implement a Queue class which implements a queue using two stacks.
    ** NOTE: Runtime be damned.
    */
    class StackQueue
    {
        Stack stack1;
        Stack stack2;
        int queueSize;

    public:
        StackQueue() : stack1(), stack2() { queueSize = 0; }

        void enqueue(int t_item) { stack1.push(t_item); }

        int dequeue()
        {
            // Move everything in stack1 until the last one to stack2
            if (stack2.isEmpty())
            {
                while (!stack1.isEmpty())
                {
                    stack2.push(stack1.pop());
                }
            }
            auto result = stack2.pop();

            // Move everything back in place
            while (!stack2.isEmpty())
            {
                stack1.push(stack2.pop());
            }
            return result;
        }
    };

    /*
    ** 3.5) Sort Stack:
    ** ----------------------------------------------------------------------
    ** Write a program to sort a stack such that the smallest items are on the
    ** top. You can use an additional temporary stack, but you may not copy the
    ** elements into any other data structure (such as an array). The stack
    ** supports the following operations: push, pop, peek, and is Empty.
    */
    static void sortStack(Stack &t_stack)
    {
        if (t_stack.isEmpty() || t_stack.size == 1)
            return;
        auto helperStack = *(new Stack());
        auto sorted = false;

        while (!sorted)
        {
            // Load onto helper stack
            while (helperStack.isEmpty() ||
                   (helperStack.peek() <= t_stack.peek()))
            {
                helperStack.push(t_stack.pop());
            }

            if (t_stack.isEmpty())
            {
                sorted = true; // sorted when everything is exhausted
                while (!helperStack.isEmpty())
                {
                    t_stack.push(helperStack.pop());
                }
            }
            else // encountered an imbalance
            {
                auto item = t_stack.pop();
                while (!helperStack.isEmpty())
                {
                    t_stack.push(helperStack.pop());
                }
                t_stack.push(item);
            }
        }
        helperStack.~Stack(); // clean up just in case
    }

    // ==============================Chapter 3=============================== //
    // ===========================Trees and Graphs ========================== //

    /** A binary search tree, where the children and its descendents on the left
     ** are smaller than the parent node and the children and its descendents on
     ** the right are larger than the parent node.
     ** */
    class BinaryTree
    {
        /* Represents a single node of a tree. */
        class TreeNode
        {
            int data;
            TreeNode *left;
            TreeNode *right;

        public:
            explicit TreeNode(int t_data)
                : data{t_data}, left{nullptr}, right{nullptr}
            {
            }
            TreeNode(int t_data, TreeNode *t_left, TreeNode *t_right)
                : data{t_data}, left{t_left}, right{t_right}
            {
            }
            int getData() { return data; }
            TreeNode *getLeft() { return this->left; }
            TreeNode *getRight() { return this->right; }
            bool hasLeft() { return this->left != nullptr ? true : false; }
            bool hasRight() { return this->right != nullptr ? true : false; }
            void setData(const int &t_data) { this->data = t_data; }
            void setLeft(TreeNode *t_left) { this->left = t_left; }
            void setRight(TreeNode *t_right) { this->right = t_right; }
            bool isLeaf() { return left == nullptr && right == nullptr; }
        };

        /* Private recursion function for printing in order*/
        void inOrderPrint(TreeNode *node)
        {
            if (node != nullptr)
            {
                inOrderPrint(node->getLeft());
                std::cout << root->getData();
                inOrderPrint(node->getRight());
            }
        }

        /* Private recursion function for printing Pre-order*/
        void preOrderPrint(TreeNode *node)
        {
            if (node != nullptr)
            {
                std::cout << root->getData();
                preOrderPrint(node->getLeft());
                preOrderPrint(node->getRight());
            }
        }

        /* Private recursion function for printing Post-order*/
        void postOrderPrint(TreeNode *node)
        {
            if (node != nullptr)
            {
                postOrderPrint(node->getLeft());
                postOrderPrint(node->getRight());
                std::cout << root->getData();
            }
        }

        TreeNode *root;
        size_t size;

    public:
        BinaryTree() : root{new TreeNode(0)}, size{0} {}
        explicit BinaryTree(const int initialValue)
            : root{new TreeNode(initialValue)}, size{1}
        {
        }

        size_t getSize() { return this->size; }

        /* Check to see if all left descendants <= n < all right descendants. In
        other words, check to make sure that this is a valid binary search
        tree.*/
        bool isValid(TreeNode *node)
        {
            auto result = true;
            if (node->isLeaf())
                return result;
            if (node->hasLeft() && (max(node->getLeft()) > node->getData()))
            {
                result = false;
            }
            if (result && node->hasRight() &&
                (min(node->getRight()) < node->getData()))
            {
                result = false;
            }
            if (!isValid(node->getLeft()) || !isValid(node->getRight()))
                result = false;
            return result;
        }

        /* Find the minimum element in a tree node*/
        int min(TreeNode *node)
        {
            auto minimum = node->getData();
            if (!node->isLeaf())
            {
                if (node->getLeft() != nullptr)
                {
                    auto leftMin = min(node->getLeft());
                    minimum = leftMin < minimum ? leftMin : minimum;
                }
                if (node->getRight() != nullptr)
                {
                    auto rightMin = min(node->getRight());
                    minimum = rightMin < minimum ? rightMin : minimum;
                }
            }
            return minimum;
        }

        /* Find the maximum element in a tree node*/
        int max(TreeNode *node)
        {
            auto maximum = node->getData();
            if (!node->isLeaf())
            {
                if (node->getLeft() != nullptr)
                {
                    auto leftMin = min(node->getLeft());
                    maximum = leftMin < maximum ? leftMin : maximum;
                }
                if (node->getRight() != nullptr)
                {
                    auto rightMin = min(node->getRight());
                    maximum = rightMin < maximum ? rightMin : maximum;
                }
            }
            return maximum;
        }

        /* Get the height of a tree, from the specified node (usually root),
        which is the number of edges from the root node to the deepest leaf
        node. */
        int getHeight(TreeNode *node)
        {
            auto height = 0;
            if (!node->isLeaf())
            {
                int leftHeight = 0, rightHeight = 0;
                if (node->hasLeft())
                {
                    leftHeight = getHeight(node->getLeft());
                }
                if (node->hasRight())
                {
                    rightHeight = getHeight(node->getRight());
                }
                height = leftHeight > rightHeight ? leftHeight : rightHeight;
                height++;
            }
            return height;
        }

        virtual void insert(int t_data)
        {
            std::cout << "some bullshit";
        }

        /* Check if a tree is complete, meaning that every level of the tree is
        fully filled, except for perhaps the last level. */
        bool isComplete(TreeNode* node)
        {
            return false;
        }

        /* A full binary tree is a binary tree in which every node has either
        zero or two children. That is, no nodes have only one child. */
        bool isFull() { return false; }

        /* A perfect binary tree is one that is both full and ocmplete. All leaf
        nodes will be at the same level, and this level has the maximum number
        of nodes.*/
        bool isPerfect() { return false; }

        void balanceTree() {}

        void printInOrder() { inOrderPrint(this->root); }
        void printPreOrder() { preOrderPrint(this->root); }
        void printPostOrder() { postOrderPrint(this->root); }
    };

    class MinHeap : public BinaryTree
    {
    public:
        void insert()
        {
        }
    };
};

int main() { return 0; }
