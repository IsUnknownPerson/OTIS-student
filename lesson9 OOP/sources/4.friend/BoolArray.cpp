#include "BoolArray.hpp"

Proxy BoolArray::operator[](std::size_t index) {
    // TODO: maybe check out of bounds
    return {*this, index};
}

bool BoolArray::operator[](std::size_t index) const {
    // TODO: maybe check out of bounds
    return storage & mask(index);
}

void BoolArray::setBit(std::size_t index, bool value) {
    const uint8_t m = mask(index);

    if (value) {
        storage |= m;
    } else {
        storage &= ~m;
    }
}

uint8_t BoolArray::mask(std::size_t index) const {
    return 1 << index;
}
