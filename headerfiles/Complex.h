#pragma once
class Complex {
    private:
        int real, imag;

    public: 
        Complex();
        Complex(int r, int i);
        void conjugate();
        void setValue(int r, int i);
        bool isEqual(Complex);
        void print();
};