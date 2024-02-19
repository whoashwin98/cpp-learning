// static keyword in CPP
#include <iostream>
using namespace std;

// there are two usages of the keyword 'static'

// inside a class definition, a static data member denotes that it will not be unique for every single object, but will be
// common for all objects. it can be accessed without having to instantiate any objects of any class. 
// static member functions are those functions which are not associated with any object and can only be used
// to modify static variables or make calls to other static member functions

class X {
    public: 
        // here we are informing the compiler that this variable exists
        static int x1;
        int x2;
        void fun() { cout << x1 << " " << x2 << endl; }
        static void statFun() { x1++; }
};

// here the definition is done to let the linker know
int X::x1;

// an example where a static function of one class, which returns an object of another class, is able to access non-static members of this (object's) class

class B {
    public: 
        int b;
        static int bStat;
        void print() {
            std::cout << "this is B's print function" << std::endl;
            std::cout << b << ", " <<  bStat << std::endl;
        }
};
int B::bStat = 123;

class A {
    public: 
        int a;
        static int aStat;

        void modifyA(int x) {
            a = x;
        }

        // to make it such that it does not affect object state, declare function as 'const'
        void print() const {
            // a = 123; ---> now this is not allowed, be it temporary or permanent objects
            std::cout << "this is A's print function" << std::endl;
            std::cout << a << ", " << aStat << std::endl;
        } 
        static B getBInstance() { return B(); }
        static A getAInstance() { return A(); }
};
int A::aStat = 456;

int main() {
    /*
    X x;
    x.x2 = 123;
    // can call static functions with or without object notation
    x.statFun();
    X::statFun();
    x.fun();

    This is because non-static methods belong to individual instances of the class and are invoked 
    using an object instance, not the class name.

    */

    // A's static function returning A's object - checking how we are able to access static and non-static member functions   
    // creating an object and then accessing
    A obj1 = A::getAInstance();
    obj1.a = 444;
    obj1.aStat = 111;
    obj1.print();

    A::getAInstance().aStat = 122;
    // the following line generates an error, because the getAInstance() function is a static one, which returns a temporary object
    // and it is an rvalue (temporary objects are rvalues since they do not have any address in memory), and we are trying to 
    // modify a temporary object which is not permitted. 
    // A::getAInstance().a = 444; 
    
    // this function will also not be able to modify the value of a, although it will not throw any compile-time errors
    // changes made to the temporary object's member variables do not last beyond this expression
    A::getAInstance().modifyA(555); 

    // there is no boundation in calling functions because they do not modify the state of the object by default
    // if we need any member function to be this way, we declare it with the 'const' keyword
    A::getAInstance().print();

    return 0;
}