#ifndef COMPLEXSHARED_LIBRARY_HPP
#define COMPLEXSHARED_LIBRARY_HPP

namespace SharedLib {
    void printMessage();
}

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

#endif //COMPLEXSHARED_LIBRARY_HPP
