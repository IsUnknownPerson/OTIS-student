#include "complex.h"
#include <iostream>
#include <math.h>

Complex::Complex() {
    std::cout << "Default constructor" << std::endl;
}

Complex::Complex(double real, double img)
    : m_real(real), m_img(img)
{
    std::cout << "constructor with arguments" << std::endl;
}

Complex::~Complex() {
    std::cout << "destructor" << std::endl;
}

double Complex::abs() const {
    return sqrt(m_real * m_real + m_img * m_img);
}

double Complex::angle() const {
    return atan2(m_img, m_real);
}

void Complex::set_real(double real) {
    m_real = real;
}

void Complex::set_img(double img) {
    m_img = img;
}
