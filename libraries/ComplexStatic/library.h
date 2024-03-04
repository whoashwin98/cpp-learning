#ifndef COMPLEXSTATIC_LIBRARY_H
#define COMPLEXSTATIC_LIBRARY_H

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

#endif //COMPLEXSTATIC_LIBRARY_H
