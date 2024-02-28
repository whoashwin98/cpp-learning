// types of casting in CPP
#include <iostream>
using namespace std;

// https://www.geeksforgeeks.org/vtable-and-vptr-in-cpp/ - IMPORTANT: VTABLE AND VPTR
// https://stackoverflow.com/questions/573294/when-to-use-reinterpret-cast - WHEN TO USE REINTERPRET_CAST

// casting: converting in between data types, which happens automatically sometimes
// note that implicit type casting only happens between pre-defined data types

// C type casting is the most liberal, it does not provide any kind of compile-time checking ability; explicit type conversion must be 
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

    // defining an explicit constructor for creating a derived class object using a base class object 
    Derived(Base b) {
        base = b.base;
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
    // automatic (implicit) casting - performed automatically by the compiler using its set of predefined rules
    float f = 3.14f;
    int i = f;
    cout << i << endl;

    // explicit type casting -  is used when you need to convert from one data type to another, which is more direct and less constrained compared to 
    // the other C++ type casts like static_cast and dynamic_cast; considered unsafe because it allows conversion among unrelated types
    // should be used only when dealing with primitive data types like int, float, double, etc.
    int j = 7;
    float g = (float) j;
    g += 0.12;
    cout << g << endl;

    // static_cast: here, conversions can be performed between pointers to related classes, both from base to derived and derived to base.
    // no safety check is performed to check for the conversions, which results in lesser overhead, upto the programmer to ensure safety
    // static_cast is more restrictive, and provides compile-time checking, plus is more readable
    
    Base b; Derived d;
    
    // (treating object d as Base)
    static_cast<Base>(d).print();   
    b = (Base) d;

    // throws error - no suitable user-defined conversion from "Base" to "Derived" exists
    // (not safe - need explicit constructor)
    // once explicit constructor defined, this does not throw any error
    static_cast<Derived>(b).print();    
    d = (Derived) b;
    

    Base *bp = new Base;
    Derived *dp = new Derived;
    // explicitly casting derived class pointer as base type, and making a base class pointer point to it - upcasting
    // it also leads to object slicing - which is a phenomenon where a derived class object is assigned to base class object, and due to this
    // the derived class data is "sliced off", leaving only the base class part. 
    bp = (Base*) dp;
    bp->print();

    // (gives unpredictable results) - downcasting - this actually leads to undefined behaviour because there is no run-time checking in the
    // C style cast, or even static_cast; thus making it a responsibility of the programmer to ensure the safety of the conversion.
    dp = (Derived*) bp;
    dp->print();
    static_cast<Derived*>(bp)->print();     

    // can also be used to perform implicit conversions (non-pointer)
    f = 3.14f;
    i = static_cast<int>(f);

    // dynamic cast: can be used only with pointers and references to objects, and its purpose is to ensure that the result of the type
    // conversion is a valid object of the requested class, otherwise it returns NULL.
    // requires the RTTI (run time type information) to keep track of dynamic types.
    // the only issue is that there is a performance overhead when we perform this kind of run-time checking.
    
    // dynamic_cast is used to convert among object pointers and references in the inheritance hierarchy.
    // this one performs a run-time check to ensure that the conversion being performed is valid
    MyDerived *der = new MyDerived;
    MyBase *base = dynamic_cast<MyBase*>(der);
    der ? cout << "Conversion Success" << endl : cout << "Conversion Failed" << endl;

    // if not, then a NULL pointer is returned, which is helpful in performing error checks.
    base = new MyBase;
    der = dynamic_cast<MyDerived*>(base);
    der ? cout << "Conversion Success" << endl : cout << "Conversion Failed" << endl;

    // reinterpret_cast: simple binary copy of the value from one pointer to another, no type checking is performed. (forced conversion)
    // allows conversion between pointer types or expression types, without any checks. it simply reinterprets the binary data
    // it  does not compile to any CPU instructions. It is purely a compiler directive which instructs the compiler to 
    // treat the sequence of bits (object representation) of expression as if it had the type new_type.

    // pointer to integer conversion
    int num = 10;
    int* ptr = &num;
    uintptr_t ptrValue = reinterpret_cast<uintptr_t>(ptr);
    std::cout << ptrValue << std::endl;         // garbage value printed
    int* ptrAgain = reinterpret_cast<int*>(ptrValue);

    // pointer to unrelated type - unsafe
    struct A{ int value; };
    struct B { double data; };
    A a; 
    a.value = 42;
    B bb = reinterpret_cast<B&>(a);
    std::cout << bb.data << std::endl;  // leads to undefined behaviour, and hence garbage value printed

    // integer to pointer
    int value = 42;
    int* ptr3 = reinterpret_cast<int*>(&value);
    std::cout << *ptr3 << std::endl;

    // const_cast: used to add or remove the 'const' or 'volatile' modifier to or from a type. allows you to perform a cast that changes the
    // constness and/or volatility of an object. 
    // useful when we need to work with legacy code where 'const' or 'volatile' is used incorrectly, and the status needs to be modified temporarily
    const int number = 100;
    const int* pointer = &number;
    // removing const from a pointer
    int* mutablePtr = const_cast<int*>(pointer);
    *mutablePtr = 101;
    std::cout << number << std::endl;           // note that the value of number still remains unchanged
    
    // adding const to a pointer
    int n = 22;
    int* newPointer = &n;
    const int* constPointer = const_cast<const int*>(newPointer);

    return 0;
}