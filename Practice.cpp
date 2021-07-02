#include <complex>
#include <iostream>
#include <string>
#include <variant>
#include <vector>

namespace Definitions
{

// Example for a variant being used
struct Entry
{
    std::string name;
    std::variant<std::vector<int>, int> v;
};

void f(Entry *pe)
{
    if (std::holds_alternative<int>(pe->v)) // does the Entry hold an int?
        std::cout << std::get<int>(pe->v);  // then get the int
}

// Example of a class of a linked list
class Node
{
private:
    int value;
    Node *next;

public:
    // Constructors
    Node() : value{0}, next{nullptr} {}
    Node(int t_val) : value{t_val}, next{nullptr} {}
    Node(int t_val, Node *t_next) : value{t_val}, next{t_next} {}

    // Accessors and Mutators
    const int &getValue() { return this->value; }
    const Node *getNext() { return this->next; }
    void setValue(const int t_value) { this->value = t_value; }
    void setNext(Node *t_next) { this->next = t_next; }

    // Destructor
};

// Example of enumeration
enum class Color
{
    red,
    white,
    blue
};

} // end namespace Definitions

int main(int argc, char *argv[])
{
    Definitions::Color e = Definitions::Color::red;

    std::vector<int> vector;
    std::vector<int>::iterator iter;
    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);
    for (iter = vector.begin(); iter < vector.end(); iter++)
    {
        std::cout << *iter;
    }

    return 0;
}
