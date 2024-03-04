#include "library.h"
#include <iostream>

ComplexStatic::ComplexStatic() : ComplexStatic(0, 0) {}
ComplexStatic::ComplexStatic(double r, double i) : re{r}, im{i} {}

void ComplexStatic::print() {
    std::cout << "Number is: " << re << (im >=0 ? " + " : " - ") << abs(im) << "i" << std::endl;
}

ComplexStatic ComplexStatic::operator+(ComplexStatic &other) {
    ComplexStatic sum;
    sum.re = this->re + other.re;
    sum.im = this->im + other.im;
    return sum;
}

ComplexStatic ComplexStatic::operator-(ComplexStatic &other) {
    ComplexStatic diff;
    diff.re = this->re - other.re;
    diff.im = this->im - other.im;
    return diff;
}

ComplexStatic ComplexStatic::operator*(ComplexStatic &other) {
    ComplexStatic prod;
    double a = this->re, b = this->im, c = other.re, d = other.im;
    prod.re = a*c - b*d;
    prod.im = a*d + b*c;
    return prod;
}

ComplexStatic ComplexStatic::operator/(ComplexStatic &other) {
    ComplexStatic div;
    if(other.re == 0 && other.im == 0) return div;

    double a = this->re, b = this->im, c = other.re, d = other.im;
    div.re = (a*c + b*d) / (c*c + d*d);
    div.im = (b*c - a*d) / (c*c + d*d);
    return div;
}