#include "Proxy.hpp"
#include "BoolArray.hpp"

Proxy::Proxy(BoolArray &parent, size_t index)
    : parent{parent},
      index{index} {}

Proxy& Proxy::operator=(bool value) {
    parent.setBit(index, value);
    return *this;
}

Proxy::operator bool() const {
    return const_cast<const BoolArray&>(parent)[index];
}
