// types of casting in CPP
#include <iostream>
using namespace std;

// casting: converting in between data types, which happens automatically sometimes
// note that implicit type casting only happens between pre-defined data types

// explicit type conversion must be used judiciously as it can be used to convert between classes
// as well as pointers to classes, which might cause run-time errors or unexpected results.
// in order to control these type of conversions, C++ provides four types of casting operators:
// static_cast, dynamic_cast, const_cast and reinterpret_cast.

class Base { 
    public: 
    int base; 
    Base() { 
        base = 123; 
    } 
    void print() { 
        cout << "Base :: print() - " << base << endl;
    } 
};

class Derived : public Base{ 
    public: 
    int der; 
    Derived() { 
        der = 456; 
    } 
    void print() { 
        cout << "Derived :: print() - " << der << endl;
    } 
};

int main() {
    /*
    // automatic (implicit) casting
    float f = 3.14f;
    int i = f;
    cout << i << endl;

    // explicit type casting
    int j = 7;
    float g = (float) j;
    g += 0.12;
    cout << g << endl;
    */

    // static_cast: here, conversions can be performed between pointers to related classes, both from base to derived and derived to base.
    // no safety check is performed to check for the conversions, which results in lesser overhead, upto the programmer to ensure safety
    
    // static_cast<Base>(d).print();   (treating object d as Base)
    // static_cast<Derived>(b).print();    (not safe - need explicit constructor)
    // static_cast<Derived*>(bp)->print();     (gives unpredictable results)

    // can also be used to perform implicit conversions (non-pointer)
    float f = 3.14f;
    int i = static_cast<int>(f);

    // dynamic cast: can be used only with pointers and references to objects, and its purpose is to ensure that the result of the type
    // conversion is a valid object of the requested class, otherwise it returns NULL.
    // requires the RTTI (run time type information) to keep track of dynamic types.
     
    // reinterpret_cast: simple binary copy of the value from one pointer to another, no type checking is performed.
    
    // const_cast: used to add or remove the const modifier to or from a type.
    
    return 0;
}