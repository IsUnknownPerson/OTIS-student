#pragma once
#include <cstddef>
#include <cstdint>
#include "Proxy.hpp"

// Недо-std::bitset размером 8 бит
class BoolArray {
public:
    Proxy operator[](std::size_t index);
    bool operator[](std::size_t index) const;
private:
    void setBit(std::size_t index, bool value);
    uint8_t mask(std::size_t index) const;
private:
    uint8_t storage{};
    friend /*class*/ Proxy;
};
