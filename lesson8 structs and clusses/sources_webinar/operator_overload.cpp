#include <string>
#include <iostream>

//operator () overload example
class LinearFunction
{
public:
    LinearFunction(double a, double b)
        : m_a(a)
        , m_b(b)
    {
    }

    double operator() (double x) const //operator () can be only a member of class
    {
        return m_a * x + m_b;
    }
private:
    double m_a;
    double m_b;
};

void linear_function_example()
{
    std::cout << "operator() overload example" << std::endl;
    LinearFunction func(2, 3); //call constructor LinearFunction(double a, double b)
    double x = 5;
    double res = func(x); // the same as: double res = func.operator()(x); , like function f(x) = 2 * x + 3
    std::cout << "Linear function f(x)=2*x + 3: x = " << x << ", f(x) = " << res << std::endl;
}

//operator [] overload example
class Vector
{
public:
    Vector(int n)
        : m_dataSize(n)
    {
        m_data = new int[m_dataSize];
        for (int i = 0; i < m_dataSize; ++i)
        {
            m_data[i] = i;
        }
    }

    //operator [] can be only a member of class
    int& operator[] (int index) //operator [] overload, return element by reference to change value
    {
        if (index < 0 || index >= m_dataSize)
            throw std::out_of_range("Vector index out of range");

        return m_data[index];
    }

    ~Vector()
    {
        delete[] m_data;
    }
private:
    int* m_data;
    int m_dataSize;
};

void vector_example()
{
    std::cout << std::endl << "operator[] overload example" << std::endl;

    Vector v(10);
    std::cout << "2nd element = " << v[1] << std::endl; //the same as: v.operator[](1);

    const int index = 5;
    std::cout << index + 1 << " element before change = " << v[index] << std::endl;

    v[index] = 333; //call operator[], the same as v.operator[](index) = 333;

    std::cout << index + 1 << " element after change = " << v[index] << std::endl;
}

int main() {
    //linear_function_example();
    vector_example();
	return 0;
}
