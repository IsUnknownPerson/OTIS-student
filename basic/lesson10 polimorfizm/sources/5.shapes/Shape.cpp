#include "Shapes.hpp"

Color Shape::getColor() const {
    return color;
}

void Shape::setColor(Color color) {
    this->color = color;
}

Point Shape::getPosition() const {
    return pos;
}

void Shape::setPosition(const Point& pos) {
    this->pos = pos;
}