// main C++ file to test the Person class
#include <iostream>
#include "Person.hpp"

// when changes are made to a header file, all sources including it, needs to be recompiled - even the most minute changes like the change in order
// of the attribute declaration - requires recompilation. in larger projects, it can cause build time issues due to the fact that even when 
// a small change to the implementation is made everyone has to wait some time until they compile their code

// one solution to this is to use the pimpl idiom (pointer to implementation) - which is used to separate implementation from the interface
// it minimises header exposures, and helps reduce build dependencies by moving private data members in a separate class, accessed through an opaque pointer
// steps to implement are given as follows: 
// 1. create a separate class for implementation
// 2. put all private members from the header into that class
// 3. define an implementation class in the header file
// 4. in the header file, create a forward declaration of a pointer pointing to this implementation class
// 5. define destructor and copy / assignment operators

int main() {
    Person p("ash");
    std::cout << p.getAttributes() << std::endl;
    return 0;
}