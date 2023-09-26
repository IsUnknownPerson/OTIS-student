#pragma once
#include "Renderer.hpp"

/**
 * Реализация-заглушка абстрактного рендера. Просто выводит в терминал
 * команды для рисования
 */
class ConsoleRenderer: public Renderer {
public:
    void drawSegment(const PointD &a, const PointD &b) override;
    void drawCircle(const PointD &center, double radius) override;
};
