// new program to learn the three main types of type casting

#include <iostream>

/*
    IMPORTANT NOTES:
    
    Explicit Type Casting: It is used when you need to convert from one data type to another, which is more direct and less constrained compared to 
    the other C++ type casts like static_cast and dynamic_cast. It is considered unsafe because it allows conversion among unrelated types. This type
    of casting should be used only when dealing with primitive data types like int, float, double, etc.
    
    static_cast<type>: It is a compile-time casting operator, which performs implicit conversions between related types, and user-defined conversions
    via constructors between unrelated types. It is safer than explicit type casting because it provides compile-type checking. It is commonly used to
    convert numerical types, upcasting in class hierarchies, and performing explicit type conversions. It is totally upto the programmer to ensure
    that the type conversion being performed is valid at compile time, because this type of cast will not be able to perform run-time checks.

    dynamic_cast<type>: It is a run-time casting operator, which ensures safe downcasting of pointers or references to objects in inheritance hierarchies.
    It allows you to safely convert pointers or references of a base class to pointers or references of a derived class. It relies on Run Time Type 
    Information (RTTI), which is a mechanism provided by C++ to obtain type information of objects at runtime. The requirement must be that, the classes
    involved must be polymorphic (at least one virtual function). Also, dynamic_cast cannot be applied to non-pointer and non-reference types because 
    other types, such as values, do not carry runtime type information in the same way pointers and references do. This cast returns the pointer or reference
    if the conversion happens successfully, otherwise it returns a nullptr.
*/

class Base {
public:
    int baseValue;
    Base(int value) : baseValue(value) {}
    virtual void print() const {
        std::cout << "Base value: " << baseValue << std::endl;
    }
};

class Derived : public Base {
public:
    int derivedValue;
    Derived(int baseVal, int derivedVal) : Base(baseVal), derivedValue(derivedVal) {}
    void print() const override {
        std::cout << "Derived value: " << derivedValue << std::endl;
    }
};

int main() {
    Derived derivedObj(100, 200);
    Base baseObj(400);

    Base* basePtr; 
    Derived* derivedPtr;

    basePtr = &baseObj; 
    // basePtr = &derivedObj; --> base class pointer pointing to derived class object
    derivedPtr = (Derived*) basePtr;

    // derivedPtr = &derivedObj; --> derived class pointer pointing to derived class object
    // derivedPtr = (Derived*) &baseObj; --> derived class pointer pointing to base class object (explicitly type casted to Derived*)
    // basePtr = (Base*) derivedPtr;

    if (derivedPtr) {
        std::cout << "Explicit casting successful:" << std::endl;
        derivedPtr->print();  
        std::cout << "derivedValue: " << derivedPtr->derivedValue << std::endl; 
    } else {
        std::cout << "Explicit casting failed" << std::endl;
    }

    // if (basePtr) {
    //     std::cout << "Explicit casting successful:" << std::endl;
    //     basePtr->print();  // Output: Derived value: 200
    // } else {
    //     std::cout << "Explicit casting failed" << std::endl;
    // }
    
    // Attempting to cast basePtr to a Derived pointer using static_cast
    // basePtr = &baseObj;
    // basePtr = &derivedObj;
    // Derived* derivedPtr_static = static_cast<Derived*>(basePtr);
    
    // derivedPtr = &derivedObj;
    // derivedPtr = static_cast<Derived*>(&baseObj);
    // Base* basePtr_static = static_cast<Base*>(derivedPtr);

    // if (derivedPtr) {
    //     std::cout << "Static casting successful:" << std::endl;
    //     derivedPtr->print();  // Output: Derived value: 200
    // } else {
    //     std::cout << "Static casting failed" << std::endl;
    // }

    // if (basePtr_static) {
    //     std::cout << "Static casting successful:" << std::endl;
    //     basePtr_static->print();  // Output: Derived value: 200
    // } else {
    //     std::cout << "Static casting failed" << std::endl;
    // }


    // Attempting to cast basePtr to a Derived pointer using explicit type casting
    // basePtr = &baseObj; --> fails
    // basePtr = &derivedObj;
    // Derived* derivedPtr_dynamic = dynamic_cast<Derived*>(basePtr);
    // derivedPtr = &derivedObj;
    // derivedPtr = (Derived*)&baseObj;
    // Base* basePtr_dynamic = dynamic_cast<Base*>(derivedPtr);

    // if (basePtr_dynamic) {
    //     std::cout << "Dynamic casting successful:" << std::endl;
    //     basePtr_dynamic->print();  // Output: Derived value: 200
    // } else {
    //     std::cout << "Dynamic casting failed" << std::endl;
    // }

    return 0;
}
