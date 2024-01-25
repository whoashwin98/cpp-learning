// string - Standard Template Library (STL) in CPP
#include <iostream>
#include <string>
using namespace std;

// there are three main components of STL:

// containers - different kinds of data structures 
// algorithms - operations on elements stored in these containers
// iterators - an abstraction for accessing containers in a sequential or random manner

// string: used to store and modify a sequence of characters which are stored contiguously.

// string_view: provides read-only view to a string (only contains a char pointer and size)
// now, memory problems will occur when strings are passed to functions, and it may lead to slowing down of performance.
// to avoid this, we can pass the string by reference, may as well make it const (if no modification is involved)
// but even after passing by reference, allocation of memory happens.
// to get away with this, we can make use of string_view.

int main() {
    
    /*
    // creating strings - constructor
    string a("First String Is The Largest String");
    cout << a << endl;

    // creating strings - assignment operator
    string b = "Second String";
    cout << b << endl;

    // accessing elements in the string
    cout << "Element of a at index 2 is: " << a.at(2) << endl;
    cout << "Element of b at index 5 is: " << b[5] << endl;
    
    // returns the first and last character of the string
    cout << a.front() << " " << a.back() << endl;

    // convert current string to C-style char*
    cout << b.c_str() << endl;

    // itereators can be used to traverse and access the elements in the string

    // functions to tell the capacity of the string
    a.empty() ? cout << "A is empty" : cout << "A is not empty";
    cout << endl;

    // shrink_to_fit reduces the memory usage to a minimum
    cout << "Capacity of A before shrinking is: " << a.capacity() << endl;
    a.shrink_to_fit();
    cout << "Capacity of A after shrinking is: " << a.capacity() << endl;

    // append to the string using append function or the += operator
    a += "asnaskjdhasdasdasdasd";
    a.append("asdauysjweriwenrwe");

    // insert characters at a specific position
    b.insert(7, "Largest ");
    cout << b << endl;

    // push_back is used to add character at the end, and pop_back is used to remove a character from the end
    b.push_back('$');
    b.pop_back();

    // clear() function is used to empty the string
    a.clear();

    // replace a specific portion of the string -- ??
    // runs in linear time
    b.replace(b.begin() + 7, b.end(), "Smallest");
    cout << b << endl;
    
    // find the first and last occurrence of a substring 
    // TC: O(N*M), where N = size of string, and M = size of substring being searched
    a = "Dummy String Here Hatralala";
    cout << a.find("tr") << endl;
    cout << a.rfind("tr") << endl;      // note: here searching happens from the back of the string

    // some of the other operations are: compare, starts_with, ends_with, contains, substr
    
    // compare returns an integer value after comparing two strings
    cout << a.compare(b) << endl;

    // substr returns a substring from the given string
    cout << a.substr(1, 7) << endl;

    // npos is a special static value which is used to indicate end of string

    // stoi is used to convert string to integer, and to_string is used to convert number to string
    
    // all the functions out of the ones used above, which involve read-only operations
    // can be used with string_view objects as well
    string_view s("Hello World");
    cout << s << endl;
    
    s[4] = 'e';     // invalid operation since lvalue cannot be modified

    */

    return 0;
}