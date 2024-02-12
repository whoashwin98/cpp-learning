// nullptr in CPP
#include <iostream>

// traditionally, in C programming, we have been using the NULL macro to represent null pointers
// it has been defined as #define NULL 0 and is treated as an integer literal with the value 0
// it is not type-safe, and cam lead to ambiguity in overloaded functions which involves both integers and pointers

// nullptr is a C++11 keyword which has specifically been designed to represent a null pointer
// this value is more type-safe, and can be implicitly converted to any other pointer type
// it can be used to initialise pointers, or to check them for nullity

void fun(int x) {
    std::cout << "int arg func called" << std::endl;
}

void fun(int* ptr) {
    std::cout << "int pointer func called" << std::endl;
}

int main() {

    int x = NULL;
    // this is allowed by the compiler, and also produces a valid result
    x = x+1;
    std::cout << x << std::endl;

    x = NULL;
    // this will lead to the integer argument function being called, which is not the desired behaviour
    fun(x);

    // compiler throws error since value is type-safe
    // int y = nullptr;
    int *y = nullptr;
    // pointer arithmetic works here
    // y = y + 1;

    if(y == nullptr) {
        std::cout << "comparison with nullptr" << std::endl;
    }
    else {
        std::cout << "given pointer is not null" << std::endl;
    }   

    // now if you call fun, the pointer one will be called since nullptr is type-safe and hence there is no ambiguity
    fun(y);

    return 0;
}