#include "Shapes.hpp"
#include <cmath>

const char* LineSegment::name() const {
    return "line";
}

void LineSegment::setLength(int length) {
    this->length = length;
}

int LineSegment::getLength() const {
    return length;
}

void LineSegment::setAngle(double angle) {
    this->angle = angle;
}

double LineSegment::getAngle() const {
    return angle;
}

int LineSegment::getWidth() const {
    // Здесь не страшно. Длина катета равна произведению длины гипотенузы на косинус прилежащего угла
    const double width = std::abs(length * std::cos(angle));
    return static_cast<int>(std::round(width));
}

int LineSegment::getHeight() const {
    // Здесь не страшно. Длина катета равна произведению длины гипотенузы на синус противолежащего угла
    const double height = std::abs(length * std::sin(angle));
    return static_cast<int>(std::round(height));
}

void LineSegment::render(Renderer& renderer) const {
    // TODO: вычисляем координаты начала и конца. Рисуем одну линию в renderer
}
