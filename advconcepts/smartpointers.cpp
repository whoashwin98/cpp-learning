// smart pointers in CPP
#include <iostream>
#include <memory>

// smart pointers are objects that act like traditional pointers, but provide automatic memory management
// they help in preventing common memory-related errors like memory leaks and dangling pointers by ensuring proper memory deallocation

// they are an implementation of the RAII idiom for managing dynamically allocated memory, by encapsulating raw pointers within objects
// when a smart pointer goes out of scope, or is explicitly reset, its destructor is called which in turn de-allocates the memory
// associated with the managed raw pointer. this ensures more robust and exception-safe code without having to explicitly use memory management calls

// C++ provides three types of smart pointers: unique_ptr, shared_ptr and weak_ptr

class Entity {
    public: 
    
    Entity() {
        std::cout << "Created Entity!" << std::endl;
    }
    
    ~Entity() {
        std::cout << "Destroyed Entity!" << std::endl;
    }
    
    void print() {}
};

int main() {

    // unique_ptr - a smart pointer that owns & manages another object through a pointer, disposes of that object when it goes out of scope
    // represents exclusive ownership of a particular object, and ensures that only one pointer can point to a resource at a time
    // move-only, and when this goes out of scope or is explicitly reset, the associated object is deleted
    {
        std::unique_ptr<Entity> entity(new Entity());
        // std::unique_ptr<Entity> copyOfEntity = entity; --> cannot be assigned as unique_ptr is only allowed to have one reference
        entity->print();
        // the object pointed by this unique_ptr is destroyed as soon as it goes out of this scope
    }

    // shared_ptr - a smart pointer that s a smart pointer that retains shared ownership of an object through a pointer
    // several shared_ptr objects may own the same object, and the object is destroyed and deallocated when one of the following happens:
    // 1. the last remaining shared_ptr owning the object is destroyed, or
    // 2. the last remaining shared_ptr owning the object is assigned another pointer using operator= or reset()

    // weak_ptr - a smart pointer that holds a non-owning ("weak") reference to an object that is managed by std::shared_ptr
    // must be converted to std::shared_ptr in order to access the referenced object
    // used along with shared pointers in order to break cyclic dependencies; does not affect the reference count of the shared pointer
    // they can be converted to shared pointers to access the object safely if it still exists
    {    
        std::shared_ptr<Entity> first;
        {
            // creating a shared_ptr using the make_shared function - more exception-safe and efficient
            // std::shared_ptr<Entity> second = std::make_shared<Entity>();
            // second = first;
            // allowed here since a shared_ptr can have more than one pointers pointing to the same object
            std::weak_ptr<Entity> second = first;
        }
        // entity still not destroyed because 'first' pointer is still alive
    }
    // now the object pointed by 'first' is destroyed as the last shared_ptr has now gone out of scope

    return 0;
}