// function pointers in CPP
#include <iostream>
#include <string>
#include <vector>

// function pointers - store addresses of a function, and it allows you to pass functions as arguments to 
// other functions, return functions from other functions and store functions in data structures
// a pointer to a function points to the address of the executable code of the function
// you cannot perform pointer arithmetic on pointers to functions.

// benefits: dynamic behaviour (determine which function to call at runtime), flexibility, and polymorphism
// downsides: code becomes complex, less readable, lacking type safety, can cause errors if dereferenced incorrectly, etc.

// example functions
void message() { 
    std::cout << "Message printed!" << std::endl; 
}

void messageWithArgs(std::string str, int value) {
    std::cout << "Message: " << str << std::endl; 
    std::cout << "Value: " << value << std::endl;
}   

// a normal function which takes one argument and returns a value
int valuePrinter(int value) {
    std::cout << "Value is: " << value << std::endl;
    return (rand() % 100);
}

// function that takes function pointer as one of the arguments
void funcWithFuncPtr(int(*funcPtr)(int), std::vector<int> vec) {
    for(auto it : vec) {
        int tempVal = funcPtr(it);
        std::cout << "Returned value: " << tempVal << std::endl;
    }
}

void first() {
    std::cout << "Message printed from first()!" << std::endl;  
}

void second() {
    std::cout << "Message printed from second()!" << std::endl;  
}

// a function that returns a function pointer - provides flexibility of getting to decide which function is being
// called during run-time - note that the functions being returned must have the same signature but names can be
// different, it is not possible to have a function return two different types of function pointers
void(*getFunction(bool cond))() {
    return (cond ? first : second);
}



int main() {

    // C++ provides the convenience of being able to assign functions to function pointers without having
    // to use the ampersand symbol in order to enhance readability - the function name itself decays into a pointer
    // auto messagePtr = message;

    // a more convenient and readable way for writing function pointer assignment (using 'auto')
    auto messagePtr = &message;

    // conventional method to write function pointer assignments
    // the syntax can be broken down into - returnType(*ptrName)(args)
    void(*messageWithArgsPtr)(std::string,int) = messageWithArgs;
    
    messagePtr();
    messageWithArgsPtr("This is a test.", 123);

    // an example of passing a function pointer to another function
    auto funcPtr = valuePrinter;
    std::vector<int> vec{1,2,3,4,5};
    funcWithFuncPtr(funcPtr, vec);

    // a function can also return a function pointer - which allows for dynamic behaviour, and decide which
    // function to be called when
    getFunction(true)();
    getFunction(false)();

    return 0;
}