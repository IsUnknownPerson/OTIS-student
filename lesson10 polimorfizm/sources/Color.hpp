#pragma once
#include <string>

// Перечисление возможных цветов
enum class Color: int {
    WHITE,
    RED,
    GREEN,
    BLUE,
    BLACK
};

// Преобразует значение color в строку. К реализации можно пока отнестись как к черному ящику
inline std::string getColorName(Color color) {
    auto list = {"white", "red", "green", "blue", "black"};
    const char* name = *(list.begin() + static_cast<int>(color));
    return {name};
}