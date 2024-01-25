#include "Complex.h"
#include <iostream>

Complex::Complex() {
    real = imag = 0;
}

Complex::Complex(int r, int i) {
    real = r;
    imag = i;
}

void Complex::conjugate() {
    imag = 0 - imag;
}

void Complex::setValue(int r, int i) {
    real = r;
    imag = i;
}

bool Complex::isEqual(Complex c) {
    return (real == c.real) && (imag == c.imag);
}

void Complex::print() {
    std::cout << "Complex Number: " << real << " + " << imag << "i" << std::endl;
}