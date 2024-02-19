// diamond problem in CPP
#include <iostream>
#include <string>

// the diamond problem is used in the context of OOP in C++ where it refers to an issue, where a class inherits
// from two classes, which in turn have a common ancestor - which leads to ambiguity in the inheritance hierarchy   

class Person {
    public: 
    std::string name;
    int age;

    Person(std::string _name, int _age) : name(_name), age(_age) {}

    void introduce() {
        std::cout << "Hello! I am " << name << " and I am " << age << " years old." << std::endl;
    }
};



int main() {
    return 0;
}