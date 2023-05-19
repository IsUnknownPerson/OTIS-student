#include "Shapes.hpp"

const char* Circle::name() const {
    return "circle";
}

void Circle::setRadius(int radius) {
    this->radius = radius;
}

int Circle::getRadius() const {
    return radius;
}

int Circle::getWidth() const {
    return 2 * radius;
}

int Circle::getHeight() const {
    return getWidth();
}

void Circle::render(Renderer& renderer) const {
    Point topLeft = getPosition();
    renderer.drawCircle({double(topLeft.x + radius), double(topLeft.y + radius)}, radius);
}
