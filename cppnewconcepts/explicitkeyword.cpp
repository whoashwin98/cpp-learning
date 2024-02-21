// implicit conversions and 'explicit' keyword in CPP
#include <iostream>
#include <string>

// https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean (WHY USE THE EXPLICIT KEYWORD)

// when you use the 'explicit' keyword with a constructor, the implicit conversion functionality gets disabled

// which means the C++ compiler stops peforming implicit conversions to the object type, and rather wants the user
// to call that constructor explicitly if they want to construct an object using that particular constructor
// for constructing an object, such a constructor must be explicitly called

// this keyword helps in preventing accidental implicit conversions, which may lead to unexpected behaviour

class Entity {
    private: 
        std::string name;
        int age;

    public: 
        Entity() : name{"unknown"}, age{-1} {}
        explicit Entity(std::string _name) : Entity() { name = _name; }
        explicit Entity(int _age) : Entity() { age = _age; }
};

int main() {
    // this line involves implicit conversion from 'int' to 'Entity' by calling of the constructor
    // Entity a = 12;           // fails when constructor is defined as explicit

    // this line does not work since RHS is a const char* and we are trying to assign it to a std::string
    // Entity b = "hello";
    // in such a case, we perform an explicit conversion from const char* to std::string or Entity
    // Entity b1 = std::string("hello");
    Entity b2 = Entity("hi");

    return 0;
}