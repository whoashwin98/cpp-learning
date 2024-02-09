// polymorphism, abstract classes and virtual functions in c++
#include<iostream> 
using namespace std;

// polymorphism - one name many forms
// there are two types of polymorphism - compile time (early binding) and run time (late binding)

// compile time polymorphism is achieved using function and operator overloading 
// run time polymorphism is achieved using virtual functions

// virtual functions are those base class member functions that can be overriden by derived classes.
// they should be accessed using a pointer of base class type to achieve runtime polymorphism.
// note that the prototype of the functions should be same in the base and derived classes for this to work.
// a virtual function can be tagged as final if we wish for it to be not inherited or overriden anymore

class BaseClass {
public:
    int var_base;
    /*
        when a pointer to base class is made to point to a derived class object, then it is able to access only the base 
        class display method here, but if the base class function is supplied with the keyword "virtual",  now the same 
        base class pointer which is pointing to a derived class object is able to access the derived class's display function.
    */

   // if the derived class does not override the base class's virtual method, then the base class method is run.
    void display() {
        cout << "Displaying Base class" << " variable var_base: " << var_base << endl;
    }
};
 
class DerivedClass : public BaseClass {
public:
    int var_derived;
    void display() {
        cout << "Displaying Base class" << "variable var_base: " << var_base << endl;
        cout << "Displaying Derived " << " class variable var_derived: " << var_derived << endl;
    }
};

// pure virtual functions: those functions which do not have any definition and are purely meant to be overriden 
// and implemented by the derived classes. 

// abstract base class: a class is known as abstract when it contains at least one of its member functions as purely virtual.
// meant to represent general concepts based on which concrete (derived) classes can be implemented.
// example: using Animal as an abstract base class (with all the common features), we can implement concrete classes like
// Human, Goat, Sheep, Lion etc. (which will have all the common features plus their own unique features)

class Base {
    public: 
        int base;
        // do-nothing function - has to be implemented in derived class
        virtual void display() = 0;
};

class Derived : public Base {
    public: 
        int derived;
        void display() {
            cout << "pure virtual function overriden" << endl;
        }
};

int main() {
    // these classes cannot have objects
    // Base b;

    Derived d;
    d.base = 23;
    d.derived = 46;
    d.display();
    cout << d.base << " " << d.derived << endl;
    /*
    // pointer to base class - this may have no information as to which derived class it may be pointing to
    BaseClass* base_class_pointer;
    BaseClass obj_base;
    DerivedClass obj_derived;
 
    // base class pointer pointing to derived class object
    base_class_pointer = &obj_derived;
    
    // this base class pointer can now only access base class members but not the derived class members
    base_class_pointer->var_base = 34;
 
    // this line of code this will cause the following error as base-class pointer cannot access the derived class variable. 
    // base_class_pointer->var_derived = 98;
 
    // this will call the base class member function
    base_class_pointer->display();
 
    base_class_pointer->var_base = 3400;
    base_class_pointer->display();
    
    // pointer to derived class
    DerivedClass* derived_class_pointer;
    derived_class_pointer = &obj_derived;
 
    // now using this pointer we can access both the base class members as well as the derived class members
    derived_class_pointer->var_base = 9448;
    derived_class_pointer->var_derived = 98;
    derived_class_pointer->display();

    */
    return 0;
}