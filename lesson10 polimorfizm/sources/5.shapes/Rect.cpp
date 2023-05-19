#include "Shapes.hpp"

const char* Rect::name() const {
    return "rect";
}

void Rect::setWidth(int width) {
    this->width = width;
}

int Rect::getWidth() const {
    return width;
}

void Rect::setHeight(int height) {
    this->height = height;
}

int Rect::getHeight() const {
    return height;
}

void Rect::render(Renderer &renderer) const {
    const double x = getPosition().x;
    const double y = getPosition().y;
    renderer.drawSegment({x, y}, {x + width, y});
    renderer.drawSegment({x + width, y}, {x + width, y + height});
    renderer.drawSegment({x + width, y + height}, {x, y + height});
    renderer.drawSegment({x, y + height}, {x, y});
}
