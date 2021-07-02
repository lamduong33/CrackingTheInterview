module;
export module Vector;

export class Vector
{
public:
    Vector(int s);
    double& operator[](int i);
    int size();
private:double* elem;
    int sz;
};

// Initialize members
Vector::Vector(int s)
    :elem{new double[s]},sz{s}{}
