// here the Log function (if not declared) throws error

// by providing the function declaration we are letting the compiler know that 
// such a function exists, not in the current file but elsewhere
// void Log(const char* msg);

// but we need to be pasting these declarations in every single file where we want 
// to use this function. so, in order to make things organised and tidy, header files are used.

// this ensures that this header file does not get included multiple times
// if not then we might face re-declaration or duplication errors
#include <iostream>

void Log(const char* msg) {
    std::cout << msg << std::endl;
}

void initLog() {
    Log("Initialising Log function...");
}