// Разберем на вебинаре "Полиморфизм и все-все-все"

#include <cstdint>
#include <vector>
#include <iostream>

using Color = uint32_t;

class Shape {
public:
    Shape() = default;
    Shape(Color color) : color{color} { }
    Color getColor() const {
        return color;
    }
    const char* name() const {
        return "shape";
    }
private:
    Color color{};
};

// parent constructor/destructor call order

class Square: public Shape {
public:
    Square() = default;

    Square(double length, Color color = Color{})
    : Shape(color) {
        setSideLength(length);
    }
    void setSideLength(double length) {
        this->length = length;
    }
    double sideLength() const {
        return length;
    }
    double area() const {
        return length * length;
    }
    const char* name() const {
        return "square";
    }
private:
    double length{};
};

void base() {
    std::vector<Square> squares = {{5., 0xffffffff}, {4., 0xff0000ff}};

    for (Square& s: squares) {
        std::cout << "Square area: " << s.area() << std::endl;
        std::cout << "Square color: " << std::hex << std::showbase << s.getColor() << std::endl;
    }

    std::vector<Shape> shapes = {Shape(0xdeadbeef), Square(4., 0xff0000ff)};

    // Square - oops
    for (Shape& s: shapes) {
        std::cout << "Shape color: " << std::hex << std::showbase << s.getColor() << std::endl;
        // s.area() - oops
        // static_cast<Square&>(s) - unsafe and error
        // dynamic_cast<Square&>(s) - CE
    }
}

class Triangle: public Shape {
public:
    const char* name() const {
        return "triangle";
    }
};

void printName(const Shape& shape, const char* realTypeName) {
    std::cout << "Shape name: " << shape.name() << " (real" << realTypeName << ")" << std::endl;
}

void printName(const Triangle& triangle, const char* realTypeName) {
    std::cout << "Triangle name: " << triangle.name() << " (real" << realTypeName << ")" << std::endl;
}

void slicing() {
    Triangle triangle;
    Square square;

    printName(triangle, "Triangle");
    printName(square, "Square");
}

int main() {
    base();
    slicing();
}