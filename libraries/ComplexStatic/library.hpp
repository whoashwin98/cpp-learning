#ifndef COMPLEXSTATIC_LIBRARY_HPP
#define COMPLEXSTATIC_LIBRARY_HPP

namespace StaticLib {
void printMessage();
}

class ComplexStatic {
public:
    double re, im;
    ComplexStatic();
    ComplexStatic(double r, double i);
    void print();
    ComplexStatic operator+(ComplexStatic& other);
    ComplexStatic operator-(ComplexStatic& other);
    ComplexStatic operator*(ComplexStatic& other);
    ComplexStatic operator/(ComplexStatic& other);
};

#endif //COMPLEXSTATIC_LIBRARY_HPP
