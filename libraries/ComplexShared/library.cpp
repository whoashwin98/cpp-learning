#include "library.hpp"
#include <iostream>

void SharedLib::printMessage() {
    std::cout << "This is ComplexShared library!" << std::endl;
}

ComplexShared::ComplexShared() : ComplexShared(0, 0) {}
ComplexShared::ComplexShared(double r, double i) : re{r}, im{i} {}

void ComplexShared::print() {
    std::cout << "Number is: " << re << (im >=0 ? " + " : " - ") << abs(im) << "i" << std::endl;
}

ComplexShared ComplexShared::operator+(ComplexShared &other) {
    ComplexShared sum;
    sum.re = this->re + other.re;
    sum.im = this->im + other.im;
    return sum;
}

ComplexShared ComplexShared::operator-(ComplexShared &other) {
    ComplexShared diff;
    diff.re = this->re - other.re;
    diff.im = this->im - other.im;
    return diff;
}

ComplexShared ComplexShared::operator*(ComplexShared &other) {
    ComplexShared prod;
    double a = this->re, b = this->im, c = other.re, d = other.im;
    prod.re = a*c - b*d;
    prod.im = a*d + b*c;
    return prod;
}

ComplexShared ComplexShared::operator/(ComplexShared &other) {
    ComplexShared div;
    if(other.re == 0 && other.im == 0) return div;

    double a = this->re, b = this->im, c = other.re, d = other.im;
    div.re = (a*c + b*d) / (c*c + d*d);
    div.im = (b*c - a*d) / (c*c + d*d);
    return div;
}