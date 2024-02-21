// the auto keyword in CPP
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <vector>
#include <list>

// https://stackoverflow.com/questions/34758042/is-there-a-downside-to-declaring-variables-with-auto-in-c (LIMITATIONS OF USING AUTO)

// there is a subtle difference between using typedef and using auto
// with typedef, we are only provding an alias for a long data type name, we have to specify that alias explicitly
// wherever required, there is no deduction of type involved, and it also does not support handling of template types

// with auto, we are telling the compiler to deduce the type of the variable with the help of the value or expression
// assigned to it - there is type deduction involved, and it also supports handling of template types

// auto is a keyword used in C++ in order to deduce the type of a variable automatically based on its initializer expression
// the focus is on the value or expression being assigned rather than the type
// this allows us to keep our code more readable especially when we are dealing with large data type names

// a function that takes a parameter specified with the auto keyword 
void print(auto value) {
    std::cout << value << "\t" << typeid(value).name() << std::endl;
}

auto mul(auto x, auto y) {
    return x * y;
}

// testing the usage of auto further - trying to break the program wherever possible
void iterateContainer(auto container) {
    for(auto it  = container.begin(); it != container.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    /*
    // an example using primitive data types on how auto deduces the data type
    auto integer = 42;
    print(integer);
    auto decimal = 42.57f;
    print(decimal);
    auto longDecimal = 42.8571;
    print(longDecimal);
    auto character = '$';
    print(character);
    // note that sometimes we might not get the type we wanted --> in such cases we need to declare the type explicitly
    auto str = "this is a string";      // type is deduced as const char *
    // std::cout << str.size();         // this line gives an error because str is a const char * and not a std::string
    print(str);
    std::string s = "this is an actual string";
    print(s);

    // another use for the auto keyword is during declaration of iterators - since the naming might get too long and
    // in turn cause difficulty to read, 'auto' comes to the rescue here and makes the code more readable
    std::unordered_map<int, std::list<int>> graph {{1, {1,2,3}}, {2, {4,5,6}}, {3, {7,8,9}}};

    // printing by explicitly specifying the type of each iterator
    std::cout << "printing without auto keyword:\n";
    for(std::unordered_map<int, std::list<int>>::iterator it = graph.begin(); 
                                                          it != graph.end(); 
                                                          it++) {
        std::cout << it->first << ": ";
        for(std::list<int>::iterator i = it->second.begin(); i != it->second.end(); i++) {
            std::cout << *i << ", ";
        } 
        std::cout << std::endl;
    }

    // printing by using the auto keyword to deduce the iterator types
    std::cout << "printing with auto keyword:\n";
    for(auto it = graph.begin(); it != graph.end(); it++) {
        std::cout << it->first << ": ";
        for(auto i = it->second.begin(); i != it->second.end(); i++) {
            std::cout << *i << ", ";
        } 
        std::cout << std::endl;
    }

    // here, since both are integers, the returned value is also of type int
    std::cout << "Division of two integers: " << typeid(mul(12, 3)).name() << std::endl;
    // here, since one of the values is of float type, the result is upgraded to float type and returned
    std::cout << "Division of one int and one float: " << typeid(mul(12.0f, 3)).name() << std::endl;
    // here, since both are floats, the returned value is also of type float
    std::cout << "Division of both floats: " << typeid(mul(12.0f, 3.0f)).name() << std::endl;
    */
    int oldArr[4] = {10,20,30,40};
    std::array<int, 5> arr{1,2,3,4,5};
    std::vector<double> vec{1.0, 2.1, 3.4, 4.7, 5.54, 6.78, 7.9, 8.0};
    std::string str{"hello world"};
    std::unordered_set<char> st{'a', 'b', 'c', 'd', 'e', 'f'};
    std::unordered_map<char, int> mp{{'a', 97}, {'b', 98}, {'c', 99}};

    iterateContainer(arr);
    iterateContainer(vec);
    iterateContainer(str);
    iterateContainer(st);

    // produces errors at run-time for these function calls
    // traditional C-style arrays decay to pointers when passed to functions, and do not have iterators
    // iterateContainer(oldArr);
    // the function written accesses elements by dereferencing, and unordered_map returns a pair which cannot be printed directly
    // iterateContainer(mp);

    // note that once type has been deduced by the compiler, it cannot be changed - since C++ is a strongly typed language
    auto var = 123;
    var = 1.23;
    std::cout << var << std::endl;
    return 0;
}