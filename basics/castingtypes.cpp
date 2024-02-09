// types of casting in CPP
#include <iostream>
using namespace std;

// casting: converting in between data types, which happens automatically sometimes
// note that implicit type casting only happens between pre-defined data types

// C type casting is the most liberal, it does not provide any kind of compile-time checking ability explicit type conversion must be 
// used judiciously as it can be used to convert between classes as well as pointers to classes, which might cause run-time errors 
// or unexpected results. in order to control these type of conversions, C++ provides four types of casting operators:
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

// classes for dynamic casting
// for this run-time check, the objects must be polymorphic (at least 1 virtual function)
class MyBase { public: virtual void test() {} };
class MyDerived : public MyBase {};

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
    // static_cast is more restrictive, and provides compile-time checking, plus is more readable
    
    Base b; Derived d;
    
    // (treating object d as Base)
    // static_cast<Base>(d).print();   
    // b = (Base) d;

    // (not safe - need explicit constructor)
    // static_cast<Derived>(b).print();    
    // d = (Derived) b;
    
    Base *bp = new Base;
    Derived *dp = new Derived;
    bp = (Base*) dp;
    bp->print();

    // (gives unpredictable results)
    dp = (Derived*) bp;
    dp->print();
    static_cast<Derived*>(bp)->print();     

    // can also be used to perform implicit conversions (non-pointer)
    float f = 3.14f;
    int i = static_cast<int>(f);

    // dynamic cast: can be used only with pointers and references to objects, and its purpose is to ensure that the result of the type
    // conversion is a valid object of the requested class, otherwise it returns NULL.
    // requires the RTTI (run time type information) to keep track of dynamic types.
    // the only issue is that there is a performance overhead when we perform this kind of run-time checking.
    
    // dynamic_cast is used to convert among object pointers and references in the inheritance hierarchy.
    // this one performs a run-time check to ensure that the conversion being performed is valid
    // MyDerived *der = new MyDerived;
    // MyBase *base = dynamic_cast<MyBase*>(der);
    // der ? cout << "Conversion Success" << endl : cout << "Conversion Failed" << endl;

    // if not, then a NULL pointer is returned, which is helpful in performing error checks.
    // MyBase *base = new MyBase;
    // MyDerived *der = dynamic_cast<MyDerived*>(base);
    // der ? cout << "Conversion Success" << endl : cout << "Conversion Failed" << endl;

    // reinterpret_cast: simple binary copy of the value from one pointer to another, no type checking is performed. (forced conversion)
    
    // const_cast: used to add or remove the const modifier to or from a type.
    
    return 0;
}