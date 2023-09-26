#include <array>
#include <iostream>
#include "BoolArray.hpp"

int main() {
    BoolArray boolArray;
    const std::array<bool, 8> source = { false, false, true, false, true, false, true, false };

    for (size_t i = 0; i < source.size(); ++i) {
        boolArray[i] = source[i];
    }

    for (size_t i = 0; i < source.size(); ++i) {
        const bool value = boolArray[i];
        std::cout << value << " ";
    }
}
