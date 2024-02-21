// new features in constructors: initialiser list and delegations
#include <iostream>
#include <string>

/*
    IMPORTANT LINKS:
    https://stackoverflow.com/questions/926752/why-should-i-prefer-to-use-member-initializer-lists (REASONS FOR USING MEMBER INITIALISER LISTS)
    https://www.learncpp.com/cpp-tutorial/delegating-constructors/ (IMPORTANT POINTS FOR DELEGATING CONSTRUCTORS)

*/

class Dummy {
    public:
        int dum;
        Dummy() { std::cout << "default ctor called" << std::endl; }
        Dummy(int _dum) { std::cout << "param ctor called" << std::endl; }
        Dummy(Dummy& other) { std::cout << "copy ctor called" << std::endl; }
};

// a class in which members are being initialised in the constructor using the normal assignment operations
// this is fine with trivial data types like integer, float, double, etc. 
// but it makes an unnecessary call to the default constructor - what happens is when we initialise this OldEntity
// object, the Dummy object is also initialised once with the default constructor, before the actual parameterised
// constructor for Dummy is called inside the OldEntity constructor

// such calling of constructors twice makes for performance issues
// whereas with initialiser lists, there is only one occurrence of calling of the constructors 
class OldEntity {
    private: 
        std::string name;
        Dummy dummy;
    
    public: 
        OldEntity() {
            // it is almost like having Dummy dummy; in this line - create a default constructed object first
            name = "unknown";
            // then another call is made to the parameterised constructor here
            dummy = Dummy(0);
        }

        OldEntity(const std::string& _name, int num) {
            name = _name;
            dummy = Dummy(num);
        }
        
        void print() {
            std::cout << "Name: " << name << std::endl;
        }
};

// using initialiser lists with constructors, avoids this unnecessary default constructor call which would save
// us from performance issues (imagine Dummy object doing heavy work like allocation of memory or opening of files)

// another reason for usage of initialiser lists is due to the constructor of base class being called first - following
// the order of construction - if your base class has only parameterised constructor, then it is necessary to use
// this member initialiser list syntax to ensure that the base constructors are called in order

// it is also used to initialise any const data members which need to be initialised separately for each entity

// it also enables us to initialise data members to the exact required state, instead of having to initialise them 
// to their default state and then changing their state to the required one

// on an additional note, it also improves the readability of code
class NewEntity {
    private: 
        std::string name;
        const int id;
        Dummy dummy;
    
    public: 
        NewEntity() : name{"Unknown"}, dummy(0), id(-1)
        { 
            // id = -1; --> cannot do this because it is a const member - have to initialise in member initialiser list
        }

        NewEntity(const std::string& _name, int num) : name(std::string(_name)), dummy(num), id(1000 + num) { }
        
        void print() {
            std::cout << "Name: " << name << std::endl;
        }
};

// delegating constructors - allows constructors to call other constructors within the same class. 
// they are particularly useful for reducing code duplication and ensuring consistent initialisation logic across
// the different constructors in a class

// class without delegating constructors
class A {
    std::string name;
    int x, y;
    int* collection;

    // this function will contain the initialisation part required to be redundantly written inside the constructors
    // so that whenever this code needs to be called, it can be done so by directly invoking this function
    // better to make it private so that only constructors and member functions are able to invoke it
    void initialise() {
        name = "default";
        // some algorithm computations
        // some other heavy work
    }

    public: 

    // it is clear that there is repitition of code, so one way around to get away with this is to create a function
    // that does this initialisation work, and it can be called in the constructor
    // one downside of this is, the programmer will have to remember to invoke this function in each of the constructor
    
    // hence, C++11 introduced something known as delegating constructors, which helps us to make calls to 
    // another constructor from one constructor
    // this gives us the advantage of not having to repeat our code, and helps reduce errors due to inconsistent initialisation

    // once delegation is being performed, there is no need to even write separate functions, we can directly
    // write the initialisation code inside this constructor, knowing that there is no scope for repitition
    A() : name{"default"}, x{0}, y{0}, collection{nullptr} {
        // initialise();
        // some algorithm computations
        // some other heavy work
    }
    
    // A(std::string _name) : name{_name}, x{0}, y{0}, collection{nullptr} {
    //     initialise();
    //     name = _name;
    // }

    // now this helps because there is no need to initialise, that work has been delegated to the default constructor
    // note that you cannot initialise any other data member if you have delegated the constructor here
    A(std::string _name) : A() {
        name = _name;
        x = 7; y = 5;
    }

    void print() {
        std::cout << name << std::endl;
        std::cout << x << std::endl;
        std::cout << y << std::endl;
        std::cout << collection << std::endl;
    }
};

// another example of a class that uses delegation of constructors
class B {
    private:
        int x, y;

    public:
        B() : B(0,0) {
            // constructor specific work here
        }

        B(int _x, int _y) : x{_x}, y {_y} {
            // can perform work intended for initialisation with respect to all constructors
        }   

        void print() { 
            std::cout << x << std::endl;
            std::cout << y << std::endl;
        }
}; 

// an example for delegating constructors involving inheritance - calling base class constructor from derived class using this method
class Base {
    public: 
    int baseVar;
    Base() : Base(-1) { std::cout << "base default ctor" << std::endl; }
    Base(int b) : baseVar(b) { std::cout << "base param ctor" << std::endl; }
};

class Derived : public Base {
    public:
    int derivedVar;
    // Derived() : Derived(-1, -1) { std::cout << "derived default ctor" << std::endl; }
    // Derived(int b, int d) : Base(b), derivedVar(d) { std::cout << "derived param ctor" << std::endl; }
    Derived(int b = -1, int d = -1) : Base(b), derivedVar(d) { std::cout << "derived constructor with values: " << b << ", " << d << std::endl; }
};

int main() {
    // OldEntity first;
    // NewEntity second;

    // A a1;
    // A a2{"hello"};
    
    // note that making the initialise function public will create problems as we might accidentally end up
    // resetting the object, and overwrite the values we were actually supposed to initialise it with
    // a2.initialise();

    // a1.print();
    // a2.print();

    // B b1, b2(1,3);
    // b1.print();
    // b2.print();

    Base b;
    Derived d1(111, 222);
    Derived d2;
    Derived d3(1);

    return 0;
}