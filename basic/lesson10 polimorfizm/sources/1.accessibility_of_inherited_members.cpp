#include "Color.hpp"
#include <string>
#include <iostream>

class Shape {
public:
    Color getColor() const { return color; }
protected:
    size_t getId() const { return id; }
private:
    Color color{Color::WHITE};
    size_t id{};
};

class ChildPublic: public Shape {
public:
    std::string toString() {
        // getColorName(color); // нельзя. color - приватное поле родителя, недоступное потомкам
        const Color shapeColor = getColor(); // Ок, доступ к public элементам родителя есть
        const size_t shapeId = getId() ; // Ок, protected-части родителя также доступны
        return "id: " + std::to_string(shapeId) + ", color: " + getColorName(shapeColor);
    }
};

void testPublic() {
    ChildPublic child;
    std::cout << child.toString() << std::endl;
    child.getColor(); // можем вызвать public метод базового класса
    // child.getId(); // Но не можем вызвать protected-метод базового класса
    // Shape().getId(); // Впрочем, его мы не можем вызвать его и напрямую у базового класса
}

class ChildProtected: protected Shape {
public:
    std::string toString() {
        // getColorName(color); // все еще нельзя. color - приватное поле родителя, недоступное потомкам
        const Color shapeColor = getColor(); // Ок, доступ к public элементам родителя есть
        const size_t shapeId = getId() ; // Ок, protected-части родителя также доступны
        return "id: " + std::to_string(shapeId) + ", color: " + getColorName(shapeColor);
    }
};

void testProtected() {
    ChildProtected child;
    std::cout << child.toString() << std::endl;
    // child.getColor(); // Теперь нельзя. public-методы базового класса теперь protected.
    // Их можно вызвать только из классов-наследников ChildProtected
}

class ChildPrivate: private Shape {
public:
    std::string toString() {
        // getColorName(color); // все еще нельзя. color - приватное поле родителя, недоступное потомкам
        const Color shapeColor = getColor(); // Ок, доступ к public элементам родителя есть
        const size_t shapeId = getId() ; // Ок, protected-части родителя также доступны
        return "id: " + std::to_string(shapeId) + ", color: " + getColorName(shapeColor);
    }
};

class Grandchild: ChildPrivate {
public:
    void foo() {
        // getColor(); // Нельзя. Теперь скрыто все, что было у дедушки
    }
};

void testPrivate() {
    ChildPrivate child;
    std::cout << child.toString() << std::endl;
    // child.getColor(); // Теперь нельзя. Ограничение стало еще строже: public-методы базового класса теперь private.
    // Т.е. теперь недоступны даже наследникам ChildPrivate
}

int main() {
    testPublic();
    testProtected();
    testPrivate();
}
