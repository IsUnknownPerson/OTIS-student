#pragma once
#include <cstddef>

class BoolArray;

class Proxy {
public:
    Proxy(BoolArray& parent, size_t index);
    Proxy& operator=(bool value);
    operator bool() const;
private:
    BoolArray& parent;
    size_t index;
};
