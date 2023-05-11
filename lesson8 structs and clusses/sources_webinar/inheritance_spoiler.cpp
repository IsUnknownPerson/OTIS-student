#include <string>
#include <iostream>
#include <math.h>

enum class Color
{
    red, //0
    green, //1
    blue  //2
};

void enum_sample()
{
    //motivation
    const int red = 0;
    const int blue = 1;
    int color = red;
    if (color == red)
        std::cout << "red color " << std::endl;
    else if (color == blue)
        std::cout << "blue color " << std::endl;

    //using enums
    Color c = Color::red;
    switch(c)  //like if-else
    {
    case Color::red:
        std::cout << "red color " << std::endl;
        break;
    case Color::green:
        std::cout << "green color " << std::endl;
        break;
    case Color::blue:
        std::cout << "blue color " << std::endl;
        break;
    }
}

class Shape
{
public:
    Shape(Color color)
        : m_color(color)
    {}

    Color GetColor() const
    {
        return m_color;
    }

    static void func() {}
private:
    Color m_color;
};

class SquareS : public Shape
{
public:
    SquareS(int length, Color color)
        : Shape(color)
        , m_length(length)
    {}

    int Square() const
    {
        func();
        return m_length * m_length;
    }


private:
    int m_length;
};

class Circle : public Shape
{
public:
    Circle(int radius, Color color)
        : Shape(color)
        , m_radius(radius)
    {}

    int Square() const
{
        return M_PI * m_radius * m_radius;
    }

private:
    int m_radius;
};

void use_shapes()
{
    int redColor = 0;

    SquareS s(5, Color::red);
    s.GetColor();

    Circle c(6, Color::green);
    c.GetColor();
}

int main() {
    use_shapes();
	return 0;
}
