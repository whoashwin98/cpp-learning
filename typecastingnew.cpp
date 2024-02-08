// new program to learn the three main types of type casting

#include <iostream>

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
