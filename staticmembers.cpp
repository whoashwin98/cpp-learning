// static keyword in CPP
#include <iostream>
using namespace std;

// there are two usages of the keyword 'static'

// inside a class definition, a static data member denotes that it will not be unique for every single object, but will be
// common for all objects. it can be accessed without having to instantiate any objects of any class. 

// static member functions are those functions which are not associated with any object and can only be used
// to modify static variables

// another usage of the keyword 'static' is done outside of the class scope (linking)
// when a variable or function is marked as static, it signifies that the linker will not be able to
// locate them during the linking process, if another file is trying to access a variable or function
// of the same name.

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



int main() {
    X x;
    x.x2 = 123;
    // can call static functions with or without object notation
    x.statFun();
    X::statFun();
    x.fun();
    return 0;
}