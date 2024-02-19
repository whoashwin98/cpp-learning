// main program for demonstrating the usage of static keyword
#include <iostream>

// another usage of the keyword 'static' is done outside of the class scope:
// 1. when used for global variables, the static keyword limits the access and visibility of that particular variable within
//    the current source file or translation unit. 
// 2. within a (non-class non-member) function, a static variable has a static storage duration - which means that it is able
//    to retain its value between function calls.
// 3. within a namespace, the static keyword limits the visibility and access of a particular variable to within the namespace

// case 1: s_var in both files is non-static, leads to linking error
// case 2: s_var is static in the other file, so now this value is printed
int s_var = 456;
// case 3: if we want to access the s_var from the other file, we use the extern keyword
// extern int s_var;

// creating a function with static variable, and one with non-static variable to see the difference
void XStatic() {
    static int x = 0;
    x++;
    std::cout << "Value of X is: " << x << std::endl;
}

void XNonStatic() {
    int x = 0;
    x++;
    std::cout << "Value of X is: " << x << std::endl;
}

int main() {
    std::cout << s_var << std::endl;

    // making multiple calls to both the static and non-static function to see the difference
    // what we observe is that, for the function with the static variable x, it is able to retain the value of x
    // even after the function call has ended, whereas the one with non-static x, it is not the case.

    XStatic();
    XStatic();
    XStatic();
    XStatic();
    XStatic();

    XNonStatic();
    XNonStatic();
    XNonStatic();
    XNonStatic();
    XNonStatic();

    return 0;
}