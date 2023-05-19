#pragma once

struct PointD {
    double x{};
    double y{};
};

/**
 * \brief Абстрактный класс - интерфейс
 * Все методы число виртуальные (=0)
 * Его наследники могут (и обязаны) каким-то образом рисовать сегменты и круги
 */
class Renderer {
public:
    virtual ~Renderer() = default;
    virtual void drawSegment(const PointD& a, const PointD& b) = 0;
    virtual void drawCircle(const PointD& center, double radius) = 0;
};