#include "DataStructures.hpp"
#include <iostream>
#include <string>

// ==================================VECTOR=====================================

template <class T>
Vector<T>::Vector() : size{0}, capacity{10}, container{new T[10]}
{
}

template <class T> Vector<T>::Vector(const int t_maxSize)
{
    this->size = 0;
    if (t_maxSize <= 0)
    {
        std::string errorMessage = "The size of the Vector has to be";
        errorMessage += "non-negative integer greater than 1";
        throw std::invalid_argument(errorMessage);
    }
    this->container = (t_maxSize >= 10) ? new T[t_maxSize] : new T[10];
}

template <class T> Vector<T>::Vector(const T *t_array, const int t_arraySize)
{
    this->size = t_arraySize / sizeof(t_array[0]);
    this->capacity = (int)this->size * 1.5;
    this->container = new T[this->capacity];
    for (int i = 0; i < this->size; i++)
    {
        this->container[i] = t_array[i];
    }
}

/* expand():
 * -------------------------------------------------------------------------
 * Expand the vector by +50% every time this is called. This is meant to be
 * used by insertion member functions to expand the vector. Do not call
 * unless there's an if check.
 */
template <class T> void Vector<T>::expand()
{
    this->capacity = (int)(this->capacity * 1.5);
    auto newContainer = new T[this->capacity];
    for (int i = 0; i < this->size; i++)
    {
        newContainer[i] = container[i];
    }
    this->container = newContainer;
}

template <class T> void Vector<T>::insert(T t_item, int t_positionIndex)
{
    if (this->size == this->capacity)
    {
        expand(); // O(n)
    }

    if (t_positionIndex <= this->size)
    {
        T temp;
        // Expansion process, only if it's not the last element. Else just add.
        if (t_positionIndex != this->size)
        {
            for (int i = t_positionIndex; i < this->capacity; i++)
            {
                temp = this->container[i + 1];
                this->container[i + 1] = this->container[i]; // NOTE: segfault
            }
        }
        this->container[t_positionIndex] = t_item;
    }
    else
    {
        throw std::out_of_range("Index out of bound for Vector.\n");
    }
    this->size++;
}

template <class T> void Vector<T>::push_back(T t_item)
{
    this->insert(t_item, this->size);
}

template <class T> T Vector<T>::remove(int t_positionIndex)
{
    T result = this->container[t_positionIndex];
    // Reduction needed if not the last element in the array
    if (t_positionIndex != this->size)
    {
        for (int i = t_positionIndex; i < this->size; i++)
        {
            this->container[i] = this->container[i + 1]; // remove
        }
    }
    this->size--;
    return result;
}

template <class T> T Vector<T>::pop() { return this->remove(this->size - 1); }

template <class T> int Vector<T>::getSize() { return this->size; }

template <class T> int Vector<T>::getCapacity() { return this->capacity; }

template <class T> void Vector<T>::toString()
{
    for (int i = 0; i < this->size; i++)
    {
        std::cout << " " << this->container[i];
    }
}

template <class T> const T Vector<T>::get(int t_index)
{
    return this->container[t_index];
}
// ========================= LINKED CONTAINER ==================================
template <class T> LinkedContainer<T>::LinkedContainer()
{
    this->size = 0;
    this->head = new Node<T>();
}

template <class T> LinkedContainer<T>::LinkedContainer(Node<T> *t_node)
{
    head = *t_node;
    while (t_node != nullptr)
    {
        this->size++;
        t_node = t_node->getNext();
    }
}

template <class T> Node<T> *LinkedContainer<T>::getHead() { return this->head; }
template <class T> int LinkedContainer<T>::getSize() { return this->size; }

template <class T> void LinkedContainer<T>::setHead(Node<T> *t_node)
{
    this->head = t_node;
}

template <class T> LinkedContainer<T>::~LinkedContainer()
{
    Node<T> *headPtr = this->getHead();
    while (headPtr != 0)
    {
        Node<T> *next = headPtr->getNext();
        delete headPtr;
        if (next != 0)
            headPtr = next;
    }
}

/* Only if the class is printable */
template <class T> void LinkedContainer<T>::printContainer()
{
    Node<T> *traversalNode = this->head;
    while (traversalNode != 0)
    {
        std::cout << this->head->getVal();
        Node<T> *nextNode = traversalNode->getNext();
        if (nextNode != 0)
            traversalNode = nextNode;
        else
            break;
    }
}

// ========================= QUEUE =============================================

template <class T> Queue<T>::Queue() { this->tail = this->getHead(); }

template <class T> Queue<T>::~Queue() {}

template <class T> Queue<T>::Queue(Node<T> *t_item)
{
    if (this->getTail() == 0)
    {
    }
    this->tail = this->getHead();
}

/* Enqueue process - add an item to the end of the queue. */
template <class T> void Queue<T>::enqueue(T t_item)
{
    Node<T> *newNode = new Node<T>(t_item);
    this->tail->setNext(newNode);
    this->tail = this->tail->getNext();
    if (this->getHead()->getVal() == "")
    {
        this->setHead(tail);
    }
}

int main(int argc, char *argv[])
{
    Queue<std::string> queue = Queue<std::string>();
    queue.enqueue(std::string("Lam"));
    queue.printContainer();
    return 0;
}
