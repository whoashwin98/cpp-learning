// default and delete functions in CPP
#include <iostream>

// https://learn.microsoft.com/en-us/cpp/cpp/explicitly-defaulted-and-deleted-functions?view=msvc-170 (DEFAULT AND DELETE CONSTRUCTORS)

// delete and default are special keywords which are used to control the behaviour of constructors
// this feature has been provided in order to have more control and managability with constructors in C++

// delete - used to explicitly delete a constructor, preventing instances of a class from being created using 
// that particular constructor; used when you want to disable a particular default, copy, move or any other constructor
// to prevent certain types of object creation

// default - used to explicitly request the compiler to generate a default implementation for a constructor that it would
// normally provide implicitly; used when you want to specify that the compiler should generate a type of constructor, even though 
// other user-defined constructors are present in the class 
// in other words, you default a constructor when you want to use the compiler-generated version, in turn you don't have to specify
// the body of that function

class Entity {
    public: 
        // Entity() {
        //     std::cout << "entity default constructor called" << std::endl;
        // }

        // default constructor now explicitly defaulted
        Entity() = default;

        // Entity(const Entity& other) {
        //     std::cout << "entity copy constructor called" << std::endl;
        // }
        // copy constructor deleted
        Entity(const Entity& other) = delete;

        ~Entity() {
            std::cout << "entity destructor called" << std::endl;
        }

        void message() {
            std::cout << "entity object message" << std::endl;
        }
};

int main() {

    Entity e1;

    // throws an error because the copy constructor has now been deleted
    // hence this operation is not allowed
    // Entity e2 = e1;

    e1.message();
    // e2.message();

    return 0;
}