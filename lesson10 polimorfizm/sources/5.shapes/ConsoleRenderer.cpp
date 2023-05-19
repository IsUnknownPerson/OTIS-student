#include <iostream>
#include <ostream>
#include "ConsoleRenderer.hpp"

inline std::ostream& operator<<(std::ostream& stream, const PointD& point) {
    return stream << "(" << point.x << ", " << point.y << ")";
}

void ConsoleRenderer::drawSegment(const PointD& a, const PointD& b) {
    std::cout << "line: [" << a << ", " << b << "]" << std::endl;
}

void ConsoleRenderer::drawCircle(const PointD& center, double radius) {
    std::cout << "circle: [" << center << ", " << radius << "]" << std::endl;
}
