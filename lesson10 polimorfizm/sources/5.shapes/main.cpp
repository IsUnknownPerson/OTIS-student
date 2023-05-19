#include "Shapes.hpp"
#include "Pi.hpp"
#include "ConsoleRenderer.hpp"
#include <vector>

std::vector<Shape*> makeShapes() {
    std::vector<Shape*> shapes;
    //new Shape; // Shape абстрактный

    Circle* circle = new Circle;
    circle->setRadius(5);
    shapes.push_back(circle);

    Rect* rect = new Rect;
    rect->setWidth(15);
    rect->setHeight(7);
    shapes.push_back(rect);
    return shapes;
}

Renderer* makeRenderer() {
    return new ConsoleRenderer();
}

int main() {
    std::vector<Shape*> shapes;
    // Создаем каким-то образом коллекцию фигур.
    // Важно, что
    // а) необходимость создания фигур того или иного типа можем
    // определить во время выполнения (не при компиляции)
    // б) можем сложить их в один контейнер (по указателям)
    shapes = makeShapes();

    // Опять же, во время выполнения можем решить, какой рендер создать.
    // У пользователя есть поддержка opengl? Создаем объект рисовальщика на opengl.
    // Нет? Рисуем в изображение. Или просто даем минималистичный вывод в консоль.
    // Единственное условие - должны унаследовать каждую из реализаций рендера от
    // интерфейса Renderer
    Renderer* renderer = makeRenderer();

    // Единообразно работаем с фигурами разных типов, при этом для
    // разных классов фигур будут вызываться разные реализации render(...)
    for (Shape* shape: shapes) {
        shape->render(*renderer);
        // Можем безопасно удалять объекты в т.ч. производных классов по указателю
        // на базовый тип - спасибо виртуальному деструктору
        delete shape;
    }
    // и здесь тоже
    delete renderer;
}