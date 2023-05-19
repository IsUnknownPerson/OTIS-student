#include "Color.hpp"
#include <vector>
#include <iostream>

// Базовый класс фигуры, в котором храним цвет и отдаем имя класса в методе name
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
    Color color{Color::WHITE};
};

/**
 * Квадрат - наследник фигуры. Добавляем к свойствам фигуры размер стороны квадрата,
 * метод вычисления площади. Пытаемся переопределить (и это не заработает) метод name
 * родителя
 */

class Square: public Shape {
public:
    Square() = default;

    Square(double length, Color color = Color{})
    : Shape(color),
      length{length} {
    }

    void setSideLength(double length) {
        this->length = length;
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

/**
 * Принимает две фигуры по ссылке. Возвращает строку "<цвет>", например, "white",
 * если цвет фигур совпадает. Иначе возвращает цвет каждой из фигур через дефис,
 * например, "blue-green"
 */
std::string mixColor(const Shape& lhs, const Shape& rhs) {
    std::string lhsColor = getColorName(lhs.getColor());

    if (lhs.getColor() == rhs.getColor()) {
        return lhsColor;
    }
    return lhsColor + "-" + getColorName(rhs.getColor());
}

/**
 * За счет наследования уже можем эффективно переиспользовать код:
 * Можем вызывать mixColor для любых public-наследников square. Без наследников
 * нам пришлось бы писать перегрузки mixColor для всех комбинаций классов фигур
 */
void colors() {
    std::cout << "colors" << std::endl;
    Shape shape(Color::RED);
    Square square(5, Color::BLUE);
    std::cout << "square+square mix: " << mixColor(square, square) << std::endl;
    std::cout << "shape+shape mix: " << mixColor(shape, shape) << std::endl;
    std::cout << "shape+square mix: " << mixColor(shape, square) << std::endl;
    std::cout << "square+square mix: " << mixColor(square, square) << std::endl;
    std::cout << "shape+shape mix: " << mixColor(shape, shape) << std::endl;
    std::cout << std::endl << std::endl;
}

/**
 * Выводит в консоль цвет фигуры shape и результат вызова метода name().
 * Дополнительно печатает строку realTypeName (в которой мы будем указывать, к какому
 * объекту относится класс фигуры)
 */
void printInfo(const Shape& shape, const char* realTypeName) {
    std::cout << "Shape color: " << getColorName(shape.getColor()) << std::endl;
    std::cout << "Shape name: " << shape.name() << " (real " << realTypeName << ")" << std::endl;
}

/**
 * Иллюстрация того, что переопределить метод name() в наследнике пока не удалось.
 * Объявляем объект square, но вызов shape.name() в printInfo выведет строку "shape",
 * т.е. вызовется метод name() базового класса shape. Причина - раннее связывание
 */
void earlyBinding() {
    std::cout << "colors" << std::endl;
    Square square;
    printInfo(square, "square");
    std::cout << std::endl << std::endl;
}

void collection() {
    std::cout << "collection" << std::endl;
    std::cout << "squares" << std::endl;
    // Помещаем в вектор (динамический массив) объекты одного типа
    std::vector<Square> squares = { {5., Color::RED}, {4., Color::GREEN} };

    // Проходим в цикле по всем квадратам. Вызов методов работат как и ожидается
    for (Square& s: squares) {
        std::cout << "Square area: " << s.area() << std::endl;
        std::cout << "Square color: " << getColorName(s.getColor()) << std::endl;
    }

    std::cout << "slicing" << std::endl;
    // Пытаемся поместить в вектор Shape'ов объекты Shape и Square (по значению !)
    // При этом тип Square "урезается" до Shape
    std::vector<Shape> shapes = { Shape(Color::RED), Square(4., Color::GREEN) };

    for (Shape& s: shapes) {
        std::cout << "Shape color: " << getColorName(s.getColor()) << std::endl;
        // s.area() - ошибка компиляции
        // static_cast<Square&>(s) - небезопасно
    }
    std::cout << std::endl << std::endl;

    std::cout << "pointers" << std::endl;

    // Если храним указатели на объекты базового типа и его наследников,
    // проблема срезки не возникает
    std::vector<Shape*> shapesPtrs = { new Shape(Color::RED), new Square(4., Color::GREEN) };

    for (Shape* s: shapesPtrs) {
        std::cout << "Shape color: " << getColorName(s->getColor()) << std::endl;

        // И технически мы можем скастовать указатель на тип-наследник и поработать с ним.
        // Но для этого мы должны понять, что s - указатель на конкретный дочерний тип.
        // "Костыль" (только для демонстрации) работает потому, что мы знаем
        // (см. инициализацию), что зеленая фигура - квадрат.
        if (s->getColor() == Color::GREEN) {
            Square* square = static_cast<Square*>(s);
            std::cout << "square area: " << square->area() << std::endl;
        }
    }

    // Здесь пока утечка памяти (забыт delete для каждого из shapesPtrs)
    // Скоро узнаем, как безопасно удалять объекты по указателю на базовый класс.
}

int main() {
    colors();
    earlyBinding();
    collection();
}