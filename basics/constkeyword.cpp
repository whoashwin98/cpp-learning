// const keyword in CPP
#include <iostream>

// the const keyword is used to specify that something is not modifiable. used in different contexts, which have been described with examples below:

// 1. using 'const' keyword inside a class - to define read-only member functions
class Example {
    int x;

    public: 
    // without the const keyword, the value is easily modifiable inside this getter class - which is only supposed to return the value of x
    // int getX() {
    //     x = 123;
    //     return x;
    // }

    // with the const keyword, now this function is not able to modify any member variables
    int getX() const {
        // x = 123;     // throws error since it is not modifiable
        return x;
    }

    void setX(int _x) {
        x = _x;
    }

    void printX() {
        std::cout << "Value of x: " << x << std::endl;
    }
};

int main() {

    Example e;
    e.setX(999);
    e.printX();

    // without const, this function changes the value of x, and would keep setting the value whenever it is called
    // with const, such changes are avoided and caught by the compiler
    std::cout << e.getX() << std::endl;
    e.printX();






    // 2. for variables, the keyword specifies that the variable cannot be modified once it has been declared as 'const'
    // these variables are better than the constants declared using preprocessor directives, since these are subject to type checking.
    int a = 333;
    const int b = 555;
    a = 444;
    // b = 222;     throws error since const values are not modifiable

    // for pointers, there are a couple of ways we can declare pointers as constant - constant with respect to value, and constant with respect to 
    // reference (and we can have const with respect to both as well)
    
    // case 1: const with respect to value - we cannot change the value pointed by the pointer, but we can change the reference
    const int* ptr1 = &a;
    // *ptr1 = 234;         // throws error because value is not mofidiable
    ptr1 = &b;

    // case 2: const with respect to reference - we cannot change the reference, but the value is modifiable
    
    // int* const ptr2 = &b; // throws error because we cannot assign a constant integer to a non-const integer pointer
    int* const ptr2 = &a;
    *ptr2 = 999;            // changes the value of 'a' to 999
    // std::cout << a << std::endl;
    // ptr2 = nullptr;      // throws error because the pointer's reference is not modifiable

    // case 3 : const with respect to both reference and value
    const int* const constPtr = &a;
    // both lines throw error as neither the value pointed nor the reference is modifiable
    // *constPtr = 123;
    // constPtr = nullptr;



    return 0;
}