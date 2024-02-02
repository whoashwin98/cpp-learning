// header files in CPP
#include <iostream>
#include "Log.h"
#include "Complex.h"
#include "Second.h"

/*
The purpose of headers, and the reason why there are two kinds of source files with names ending in different 
extensions, is for the headers to provide declarations for things that are compiled elsewhere. If you put 
function definitions in a file that you then include in a bunch of places, then you are compiling a copy 
of that function in each one of those places. When you then link your program, you get redefinition errors 
because you have multiple function definitions for the same functions.

You also don't generally want to compile any more stuff than just the file you've just changed when 
you build. In particular, you don't want to recompile the entire standard library every time you 
compile your program, which would happen if the source code of the library was actually in the headers 
you include. But no, it's already been compiled, and all you want is to link with it — but for the 
compiler to be able to compile your code, you need to give it the declarations for the library and 
other stuff that's already been compiled, so that it can compile the calls to those functions correctly. 
*/

int main() {
    /*
    initLog();
    Log("Hello World!");

    std::cout << std::endl;

    Complex c1;
    c1.setValue(7, 12);
    c1.print();

    Complex c2(7, 12);
    c2.print();
    c2.isEqual(c1) ? std::cout << "c1 and c2 are equal" : std::cout << "c1 and c2 are not equal";

    std::cout << std::endl;
    
    c2.conjugate();
    c2.print();

    */

    secondFunc();
    firstFunc();
    
    return 0;
}