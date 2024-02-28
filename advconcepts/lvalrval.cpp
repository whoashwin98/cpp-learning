// lvalues, rvalues, lvalue references and rvalue references in CPP
#include <iostream>
#include <utility>

// lvalues refer to objects that have a persistent identity and can be assigned a value
// expressions that represent a memory location such as variables or references are examples of lvalues

// lvalue references are those which can only bind to lvalues - used for aliasing existing objects, and also to pass values by reference to functions
// when a function returns an lvalue reference, it can appear on the LHS of assignment operator
// note that const lvalue references can bind to rvalues, but non-const lvalue references cannot

// ravlues refer to temporary or transient values, which do not have a persistent identity
// literals (constants like numbers or strings), values returned from functions, and temporary expressions are examples of rvalues
// they cannot be assigned any value because they do not have any memory location bound to them

// rvalue references are those which can bind to rvalues - used to forward arguments to other functions, move semantics, and reduce copying overhead
// they are used to extend the lifetimes of temporary objects

void lvalue_demo(int& ref) {
    std::cout << "Inside lvalue_demo, received lvalue: " << ref << std::endl;
}

void rvalue_demo(int&& rref) {
    std::cout << "Inside rvalue_demo, received rvalue: " << rref << std::endl;
}

void func(const int& x) {
    std::cout << "Const lvalue reference method called..." << std::endl;
}

void func(int&& x) {
    std::cout << "rvalue reference method called..." << std::endl;
}

int main() {
    int x = 42;
    int y = 100;

    // lvalue reference
    int& lref = x;

    // rvalue reference
    int&& rref = std::move(y); // using std::move to convert y to an rvalue

    // using lvalue and rvalue references
    lvalue_demo(x); 
    rvalue_demo(std::move(y));

    // assigning rvalue to const lvalue reference
    const int& const_lref = 123;
    std::cout << "Value of const_lref: " << const_lref << std::endl;

    // checking which out of const lvalue ref or rvalue ref methods are called in different cases

    func(x);
    func(std::move(x));
    func(1);

    return 0;
}
