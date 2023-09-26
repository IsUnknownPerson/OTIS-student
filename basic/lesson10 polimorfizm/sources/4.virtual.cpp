#include <iostream>

class Shape {
public:
    /**
     * Ключевое слово virtual дает нам т.н. "позднее связывание".
     * В каждом объекте теперь хранится указатель на таблицу функций.
     * Адреса в таблице могут быть заменены в дочерних объектах
     */
    virtual const char* name() const {
        return "shape";
    }
};

class Square: public Shape {
public:
    const char* name() const { // virtual is through
        return "square";
    }
};

void printInfo(const Shape& shape, const char* realTypeName) {
    std::cout << "Shape name: " << shape.name() << " (real " << realTypeName << ")" << std::endl;
}

int main() {
    Shape shape;
    printInfo(shape, "shape");
    Square square;
    // Теперь внутри printInfo будет вызван метод Square, а не Shape.
    printInfo(square, "square");

    // Размер пустого класса вырос: теперь там лежит скрытый указатель
    // на таблицу виртуальных функций
    std::cout << "sizeof(Shape) " << sizeof(Shape) << std::endl;
}