// class basics - order of running of constructors and destructors
// note that the order followed by constructors and destructors is - first constructed, last destructed.
#include <iostream>
using namespace std;

class A {
    public: 
        A() {
            cout << "Object of A constructed." << endl;
        }

        ~A() {
            cout << "Object of A destructed." << endl;
        }
};

class B {
    public: 
        B() {
            cout << "Object of B constructed." << endl;
        }

        ~B() {
            cout << "Object of B destructed." << endl;
        }
};

class C {
    public: 
        C() {
            cout << "Object of C constructed." << endl;
        }

        ~C() {
            cout << "Object of C destructed." << endl;
        }
};


int main() {
    A a;
    C c;
    B b;
    return 0;
}
