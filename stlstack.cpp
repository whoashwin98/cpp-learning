// stack STL in CPP
#include <iostream>
#include <stack>
#include <deque>
#include <string>
#include <vector>
#include <list>

/*
    IMPORTANT LINKS: 
    https://chat.openai.com/c/7cc0ae7b-71b5-418c-8e33-1c13aafaadc5 (STACK OVERVIEW)
    https://stackoverflow.com/questions/63043291/stdstack-implementation-on-different-containers-what-is-the-actual-difference (STACK CONTAINER SELECTION SCENARIOS)
*/

// container adaptors are wrappers around the existing container classes, providing a specific
// interface for performing certain operations - tailored to a specific use case or data structure
// they do not encapsulate their own storage, rather they use an underlying container to manage the elements

// stack is a container adaptor, which provides Last In First Out (LIFO) functionality
// the underlying container used to manage the stack is deque by default, but we can give any container
// that satisfies the properties of SequenceContainer

// use case for stack comes in when we need to have the most recent result ready to be fetched, like a cache
// undo functions, backtracking algorithms, etc.

struct A {
    std::string s;
    A(std::string str) : s(std::move(str)) { std::cout << " constructed\n"; }
    A(const A& o) : s(o.s) { std::cout << " copy constructed\n"; }
};

void printDeqStack(std::stack<int> st) {
    std::cout << "Deque Stack: ";
    while(!st.empty()) {
        std::cout << st.top() << " ";
        st.pop();
    }
    std::cout << std::endl;
}

void printVecStack(std::stack<int, std::vector<int>> st) {
    std::cout << "Vector Stack: ";
    while(!st.empty()) {
        std::cout << st.top() << " ";
        st.pop();
    }
    std::cout << std::endl;
}

void printListStack(std::stack<int, std::list<int>> st) {
    std::cout << "List Stack: ";
    while(!st.empty()) {
        std::cout << st.top() << " ";
        st.pop();
    }
    std::cout << std::endl;
}

int main() {
    // creating a stack initially containing elements from a deque
    std::deque<int> dq{1,2,3,4,5,6};
    std::vector<int> vec{11,22,33,44,55,66};
    std::list<int> lis{101,102,103,104,105,106};

    // uses deque as the default underlying container
    std::stack<int> deqStack(dq);
    // uses std::vector as its underlying container
    std::stack<int, std::vector<int>> vecStack(vec);
    // uses std::list as its underlying container
    std::stack<int, std::list<int>> lisStack(lis);

    // there are no iterators - to print the stack we need empty it to print all elements
    std::cout << "Initial stack contents:\n";
    printDeqStack(deqStack);
    printVecStack(vecStack);
    printListStack(lisStack);

    // push - inserts an element to the TOS
    deqStack.push(12);
    vecStack.push(123);
    lisStack.push(-8);
    std::cout << "After push:\n";
    // top - get the current TOS
    std::cout << "deqStack TOS: " << deqStack.top() << std::endl;
    std::cout << "vecStack TOS: " << vecStack.top() << std::endl;
    std::cout << "lisStack TOS: " << lisStack.top() << std::endl;
    printDeqStack(deqStack);
    printVecStack(vecStack);
    printListStack(lisStack);

    // pop - removes the TOS
    std::cout << "After 2 pops:\n";
    deqStack.pop(); deqStack.pop();
    vecStack.pop(); vecStack.pop();
    lisStack.pop(); lisStack.pop();
    std::cout << "deqStack TOS: " << deqStack.top() << std::endl;
    std::cout << "vecStack TOS: " << vecStack.top() << std::endl;
    std::cout << "lisStack TOS: " << lisStack.top() << std::endl;
    printDeqStack(deqStack);
    printVecStack(vecStack);
    printListStack(lisStack);

    // size - gives the size of the stack
    std::cout << "Size of deqStack: " << deqStack.size() << std::endl;
    std::cout << "Size of vecStack: " << vecStack.size() << std::endl;
    std::cout << "Size of lisStack: " << lisStack.size() << std::endl;
   
    // emplace functions take an array of arguments and pass it to the object's class constructor which is then invoked
    // insert function requires an already constructed object as its argument, and as a result, a copy constructor is invoked during insertion
    // demonstrating emplace in std::stack
    /*
    std::stack<A> st;

    std::cout << "construct 2 times A:\n";
    A three { "three" };
    A four { "four" };
    
    std::cout << "insert:\n";
    A one("one");
    st.push(one);

    std::cout << "emplace:\n";
    st.emplace("two");
    */

    return 0;
}