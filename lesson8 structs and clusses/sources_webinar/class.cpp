#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include "complex.h"

class PointAkaStruct
{
    int x;
    int y;
};

class SimplePoint
{
public:
    SimplePoint(int x, int y) //constructor
        : m_x(x)
        , m_y(y)
    {
        std::cout << "Point ctor" << std::endl;
    }

    SimplePoint(int x)
        : m_x(x)
        , m_y(10)
    {}


    SimplePoint() = default;

    void init(int x, int y)
    {
        m_x = x;
        m_y = y;
    }


private:
    int m_x;
    int m_y;
};

void point_constructor()
{
    PointAkaStruct p1;
    SimplePoint p2; //won't compile
    p2.init(2, 3);

    SimplePoint p3(2, 3);
    //std::cout << p3.m_x; //won't compile
}

class Point
{
public:
    Point(int x, int y) //constructor
        : m_x(x)
        , m_y(y)
    {
        print_coordinates();
        std::cout << "Point constructor" << std::endl;
    }

   // Point() = default; // generate default constructor forcefully

    void print_coordinates()
    {
        std::cout << "Point x=" << m_x << " y=" << m_y << std::endl;
    }

    int get_x() const
    {
        //m_x += 1; //won't compile
        return m_x;
    }

    int get_y() const
    {
        return m_y;
    }

    ~Point() //destructor, no params, no return value
    {
        std::cout << "Point destructor" << std::endl;
    }

private:
    int m_x;
    int m_y;
    const int x = 5;
};

void point_constructor_destructor()
{
    Point p(1, 2);
    p.print_coordinates();
    //p.~Point(); //BAD! do not call destructor
}

int main() {
    point_constructor_destructor();

    {
        Point p(4, 5);
    }

    Complex complex2 {42.0, 13.0};
    Complex complex3 (42.0, 13.0);

	return 0;
}
