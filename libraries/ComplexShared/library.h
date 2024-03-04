#ifndef COMPLEXSHARED_LIBRARY_H
#define COMPLEXSHARED_LIBRARY_H

class ComplexShared {
public:
    double re, im;
    ComplexShared();
    ComplexShared(double r, double i);
    void print();
    ComplexShared operator+(ComplexShared& other);
    ComplexShared operator-(ComplexShared& other);
    ComplexShared operator*(ComplexShared& other);
    ComplexShared operator/(ComplexShared& other);
};
#endif //COMPLEXSHARED_LIBRARY_H
