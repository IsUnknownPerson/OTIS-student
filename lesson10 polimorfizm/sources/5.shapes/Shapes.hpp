#pragma once
#include "../Color.hpp"
#include "Point.hpp"
#include "Renderer.hpp"

// Объявления иерархии фигур

class Shape {
public:
    virtual ~Shape() = default;
    virtual const char* name() const = 0;
    Color getColor() const;
    void setColor(Color color);
    Point getPosition() const;
    // Положение фигуры в пространстве может меняться только при вызове этого метода
    void setPosition(const Point& pos);
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    // Определяет способ отображения фигуры с использованием абстрактного Renderer.
    // Класс Renderer лишь описывает интерфейс, не предлагая никакой готовой реализации
    // Благодаря этому Shape и его наследники абстрагированы от деталей рисования
    // (работа с пикселями, графическими контекстами и т.д.), ничего о них не знают
    virtual void render(Renderer& renderer) const = 0;
private:
    Color color{Color::WHITE};
    Point pos; // верхний левый угол ограничивающего фигуру прямоугольника
};

class Circle: public Shape {
public:
    const char* name() const override;
    void setRadius(int radius);
    int getRadius() const;
    int getWidth() const override;
    int getHeight() const override;

    void render(Renderer &renderer) const override;

private:
    int radius{};
};

class Rect: public Shape {
public:
    const char* name() const override;
    void setWidth(int width);
    int getWidth() const override;
    void setHeight(int height);
    int getHeight() const override;
    void render(Renderer &renderer) const override;
private:
    int width{};
    int height{};
};

/**
 * \brief Класс, описывающий сегмент линии (отрезок)
 * С этим классом ситуация сложнее. Пример того, что бывает, если не
 * слишком задумываться при создании базового класса.
 * 1. Задавать концы отрезка (частый способ задания отрезка) мы не можем,
 * т.к. при этом изменим Shape::pos. Ок, здесь мы можем извернуться и
 * задавать только длину сегмента и угол его поворота. Тогда сохраним
 * инвариант базового класса - положение меняется только вызовом setPosition()
 * 2. Размеры bbox'а в интерфейсе базового класса "пообещали" отдавать
 * в int'ах. Повернутый отрезок в общем случае будет иметь не целые
 * координаты конечных точек. В качестве костыля сейчас округляем
 * getWidth(), getHeight() до целых. В зависимости от того, для каких
 * целей используем bbox это может быть допустимым поведением,
 * может сломать логику. В качестве альтернативы можно округлять вверх.
 * Если бы при проектировании базового класса подумали о типах данных,
 * этих проблем избежали бы
 */
class LineSegment: public Shape {
public:
    const char* name() const override;
    // Не можем реализовать такой интерфейс...
    // void setA(const Point& p);
    // void setB(const Point& p);

    void setLength(int length);
    int getLength() const;
    void setAngle(double angle);
    double getAngle() const;
    int getWidth() const override;
    int getHeight() const override;
    void render(Renderer &renderer) const override;
private:
    int length{};
    double angle{};
};