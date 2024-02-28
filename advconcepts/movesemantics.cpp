// move semantics in CPP
#include <iostream>
#include <string>

/*
    IMPORTANT LINKS:
    https://stackoverflow.com/questions/28627348/noexcept-and-copy-move-constructors (WHY MOVE CONSTRUCTORS COME WITH NOEXCEPT KEYWORD)
    https://stackoverflow.com/questions/3106110/what-is-move-semantics (MOVE SEMANTICS EXPLAINED FROM SCRATCH)
*/

// move semantics enables us to perform efficient resource transfer from one object to another ('steal') while avoiding unnecessary copying
// facilitated by rvalue references - important where resource management is a critical aspect and you cannot afford having too many copying operations
// principles of move semantics are described below: 
// 1. allows objects to transfer their resources (dynamically allocated memory or files) from one object to another by reassigining the internal pointers;
//    essentially the transfer of ownership is what happens 
// 2. by utilizing this, we are able to avoid unnecessary copying especially for those objects which are too expensive to copy. 

// std::move is a utility function that enables converting an lvalue to an rvalue - so that it can be bound to an rvalue reference
// helps us in performing "efficient transfer" of resources from source to destination - by itself it does not perform any moving

// an example class with dynamic memory allocation to demonstrate move semantics
class Collection {
    private: 
        int* data;
    
    public: 
        // default constructor which delegates the parameterised constructor
        Collection() : Collection(0) {
            std::cout << "default constructor!" << std::endl;
        }

        // constructor with the explicit keyword - making sure it has to be called and there is no implicit (unwanted) data conversion taking place
        explicit Collection(int size) {
            data = new int[size];
            std::cout << "constructor!" << std::endl;
        }   

        // copy constructor with const lvalue reference
        Collection(const Collection& other) {
            std::cout << "copy constructor!" << std::endl;
            data = new int[sizeof(other)];
            std::copy(other.data, other.data + sizeof(other), data);
        }   

        //  copy assignment operator with const lvalue reference
        Collection& operator=(const Collection& other) {
            if(this != &other) {
                std::cout << "copy assignment!" << std::endl;
                delete[] data;
                data = new int[sizeof(other)];
                std::copy(other.data, other.data + sizeof(other), data);    
            }
            return *this;
        }

        // move constructor
        Collection(Collection&& other) noexcept {
            std::cout << "move constructor!" << std::endl;
            data = other.data;
            other.data = nullptr;
        }

        // move assignment operator
        Collection& operator=(Collection&& other) noexcept {
            if(this != &other) {
                std::cout << "move assignment!" << std::endl;
                delete[] data;
                data = other.data;
                other.data = nullptr;
            }
            return *this;
        }

        // destructor
        ~Collection() {
            std::cout << "destructor!" << std::endl;
            delete[] data;
        }
};



int main() {
    // regular object creation
    Collection c1(7);
    std::cout << std::endl;

    // copy constructors
    Collection c2(8);
    Collection c3 = c2;
    std::cout << std::endl;

    // copy assignment
    Collection c4;  
    c4 = c1;
    std::cout << std::endl;

    // move constructor
    Collection c5(std::move(c2));
    std::cout << std::endl;

    // move assignment
    c5 = std::move(c1);
    std::cout << std::endl;

    return 0;
}