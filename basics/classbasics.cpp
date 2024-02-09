// class basics - data members, member functions, types of constructors and access specifiers
#include <iostream>
using namespace std;

// the rule of 3: if a class defines any one of these three constructors then it should define
// all of them - constructor, destructor, and copy constructor (also include copy assignment operator)
// the destructor becomes optional when we are using any data structure which will be able to deallocate itself

// access specifiers for classes: private, protected and public
// private: members are accessible only inside the class, by member & friend functions, and cannot be inherited.
// protected: members are accessible only inside the class, by member & friend functions, and can be inherited.
// public: members are accessible both inside and outside the class, and can be inherited.

class Complex {
    private: 
        int re, im;
    
    public: 
        // default constructor
        Complex() {
            cout << "Object Constructed" << endl;
        }

        // parameterised constructor - able to take arguments and assign them to the data members
        Complex(int re, int im) {
            this->re = re;
            this->im = im;
        }

        // copy constructor - takes reference of object as argument 
        // used to copy the values of existing object into the newly created object
        Complex(Complex &c) {
            re = c.re;
            im = c.im;
        }

        // member function defined inside the class
        void display() {
            cout << re << " + " << im << "i" << endl;
        }

        // member function defined outside the class (only declaration here)
        void takeInput();

        // destructor - cannot have arguments, cannot be overloaded, should be declared in the public section of the class, 
        ~Complex() {
            cout << "Object Destructed" << endl;
        }
};

// member function declared inside the class but definition written outside the class
void Complex::takeInput() {
    int r, i;
    cin >> r >> i;
    re = r; 
    im = i;
}

int main() {
    Complex C1(3, 4);
    Complex* C2 = new Complex();

    C1.display();
    C2->display();

    return 0;
}