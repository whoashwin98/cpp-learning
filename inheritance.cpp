// inheritance and its types
#include <iostream>
using namespace std;

// inheritance - the phenomenon by which a class derives some properties from another class.
// sub-class is the class that inherits the properties, and super-class is the class from which the properties are inherited.

// why should inheritance be used - IMPORTANT.
// NOTE: private members are not inherited, and by default inheritance is private.

// there are three modes of inheritance: public, private and protected 
// when a class is inherited as public, all of its public members become public members of the derived class, and the same goes for protected members.
// when a class is inherited as protected, all of its public and protected members become protected members of the derived class.
// when a class is inherited as private, all of its public and protected members become private members of the derived class.

/*
class A {
    public:
        int x;

    protected:
        int y;

    private:
        int z;
};

class B : public A {
	// x is public
	// y is protected
	// z is not accessible from B
};

class C : protected A {
	// x is protected
	// y is protected
	// z is not accessible from C
};

class D : private A // 'private' is default for classes
{
	// x is private
	// y is private
	// z is not accessible from D
};
*/

// the types of inheritance possible in C++ are: single, multi-level, multiple, hierarchical and hybrid.

// in multiple inheritance, it is possible that a class inherits the traits of another class more than once (consider the following example
// where Person is inherited twice by Child) - which leads to ambiguity for the compiler.

// one solution to this is to use the scope resolution operator (::) whenever handling such cases
// another solution is to use virtual inheritance - which makes sure that such classes are inherited only once when moving down
// the hierarchy thus making sure there is no ambiguity.

// note: order of constructors called in inheritance hierarchy: base to derived constructed, derived to base destructed.

class Person { 
	public:
		Person() { cout << "Person::Person() called" << endl; }
		Person(int x)  { cout << "Person::Person(int) called" << endl; }
		~Person() { cout << "Person object destructed" << endl; }
};
 
class Father : virtual public Person { 
	public:
		Father() {}
		Father(int x) : Person(x)   {
		cout << "Father::Father(int) called" << endl;
		}
		~Father() { cout << "Father object destructed" << endl; }
};
 
class Mother : virtual public Person { 
	public:
		Mother() {}
		Mother(int x) : Person(x) {
			cout << "Mother::Mother(int) called" << endl;
		}
		~Mother() { cout << "Mother object destructed" << endl; }
};
 
class Child : public Father, public Mother  { 
	public:
		Child() {}
		Child(int x) : Mother(x), Father(x) {
			cout << "Child::Child(int) called" << endl;
		}
		~Child() { cout << "Child object destructed" << endl; }
};


int main() {
	Child child;
    return 0;
}