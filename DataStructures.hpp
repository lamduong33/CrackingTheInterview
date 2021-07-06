#ifndef __DATASTRUCTURES_H_
#define __DATASTRUCTURES_H_

/*
** A Vector that changes size by +50% every time an insertion request exceed its
** size.
*/
template <class T> class Vector
{
public:
    // Default constructor that will create an empty array for 10 items.
    Vector();

    // Constructor for Vector that specifies the size
    Vector(const int t_capacity);

    // Constructor for turning a static array into a vector
    Vector(const T *t_array, const int t_arraySize);

    // Expand when too small
    void expand();
    const T get(int index);

    /*
    ** Function to insert an element at the end of the list
    */
    void insert(T t_item, int t_positionIndex);
    void push_back(T t_item);
    T pop();
    T remove(int t_positionIndex);
    void toString();
    int getSize();
    int getCapacity();

    // Destructor
    ~Vector() { delete[] container; }

private:
    int size, capacity;
    T *container; // the actual container of the object
    void adjustSize();
};

/* ============================= NODE ======================================= */
template <class T> class Node
{
public:
    Node() : val{0}, next{0} {}; // Has to be 0 and not nullptr for templates.
    Node(T t_val) : val{t_val}, next{0} {};
    Node(T t_val, Node *t_next) : val{t_val}, next{t_next} {};
    T getVal() { return this->val; };
    Node<T> *getNext() { return this->next; };
    void setNext(Node<T> *t_nextNode) { this->next = t_nextNode; };
    //~Node() { delete next; };

private:
    T val;
    Node<T> *next;
};

/* LinkedContainer superclass for linked data structures such as LinkedList,
 * Queue, Stack. This is an abstract class. */
template <class T> class LinkedContainer
{
public:
    LinkedContainer(); // the only concrete thing about the class
    LinkedContainer(Node<T> *t_node);
    virtual int getSize();
    virtual Node<T> *getHead();
    virtual void setHead(Node<T> *t_node);
    virtual void printContainer();
    virtual ~LinkedContainer() = 0;

private:
    int size;
    Node<T> *head;
};

// Queue: first in - first out
template <class T> class Queue : public LinkedContainer<T>
{
public:
    Queue();
    Queue(Node<T> *t_node);
    void enqueue(T t_item);
    Node<T> *getTail();
    T dequeue();
    ~Queue();

private:
    Node<T> *tail;
};

template <class T> class Stack
{
};

template <class T> class LinkedList
{
};

template <class T> class BinaryTree
{
};

template <class T> class RedBlackTree
{
};

#endif // __DATASTRUCTURES_H_
