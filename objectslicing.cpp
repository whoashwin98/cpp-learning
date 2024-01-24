// object slicing 
#include <iostream>
using namespace std;

// when a derived class object is created and initialised with values, and then a base class object is created and the derived
// class object is assigned to it, only the base class attributes present in the derived class object are copied.
// the values which are native only to the derived class are not copied to this base class object.
// this is known as object slicing

class Base {
    public: 
        int x;
        void baseFun() {
            cout << "Base Function" << endl;
            cout << x << endl;
        }
};

class Derived : public Base {
    public: 
        int y;
        void derivedFun() {
            cout << "Derived Function" << endl;
            cout << x << endl;
            cout << y << endl;
        }
};

int main() {
    Derived d;
    d.x = 12;
    d.y = 23;
    
    d.derivedFun();

    // value of x is copied but y is not
    Base b = d;
    b.baseFun();

    return 0;
}