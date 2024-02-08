// queue STL in CPP
#include <iostream>
#include <queue>
#include <deque>
#include <list>
#include <vector>
#include <string>

/*
    IMPORTANT LINKS:
    https://chat.openai.com/c/1c49e361-84bc-4826-bfa6-4aa5e37c6b01 (QUEUE OVERVIEW)
    https://stackoverflow.com/questions/41102465/why-does-stdqueue-use-stddequeue-as-underlying-default-container (WHY DEQUE IS THE DEFAULT CONTAINER)
*/

// queue is a container adaptor, which provides First In First Out (FIFO) functionality
// the underlying container used to manage the queue is std::deque by default, but we can use any other container which satisfies the requirements
// of SequenceContainer, and it provides the functionality of inserting at the end and deleting from the front
// for std::queue, the containers which can be used are: std::deque and std::list

// use cases for queues are wherever we need to process elements in the order in which they arrived, such as BFS algorithms or event processing systems

struct A {
    std::string s;
    A() : s("null") { std::cout << " default constructed\n"; }
    A(std::string str) : s(std::move(str)) { std::cout << " constructed\n"; }
    A(const A& o) : s(o.s) { std::cout << " copy constructed\n"; }
};

void printDeqQueue(std::queue<int> q) {
    std::cout << "Deque Queue: ";
    while(!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << std::endl;
}

void printLisQueue(std::queue<int, std::list<int>> q) {
    std::cout << "List Queue: ";
    while(!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << std::endl;
}

int main() {
    /*
    // creating a queue initially containing some elements 
    std::deque<int> dq{1,2,3,4,5,6};
    std::list<int> lis{11,22,33,44,55,66};
    std::vector<int> vec{101,102,103,104,105,106};

    // uses std::deque as the default underlying container
    std::queue<int> deqQueue(dq);
    // uses std::list as its underlying container
    std::queue<int, std::list<int>> lisQueue(lis);

    // note that no compile errors are produced when a queue is created with std::vector as its underlying container
    std::queue<int, std::vector<int>> vecQueue(vec);
    // no errors produced here as well - since insertion happens at the back and std::vector has functions for that
    vecQueue.push(1);
    // compile error here since there is no in-built function (constant time) that removes an element from the front of a vector
    // vecQueue.pop();

    // there are no iterators - to print the queue we need to empty it
    std::cout << "Initial queue contents:\n";
    printDeqQueue(deqQueue);
    printLisQueue(lisQueue);

    // push - inserts an element at the end of the queue
    deqQueue.push(7);
    lisQueue.push(77);
    std::cout << "After push:\n";

    // front - get the current front element of the queue
    // back - get the current back element of the queue
    std::cout << "deqQueue front and back: " << deqQueue.front() << ", " << deqQueue.back() << std::endl;
    std::cout << "lisQueue front and back: " << lisQueue.front() << ", " << lisQueue.back() << std::endl;
    printDeqQueue(deqQueue);
    printLisQueue(lisQueue);

    // pop - removes the element from the front of the queue
    deqQueue.pop(); deqQueue.pop();
    lisQueue.pop(); lisQueue.pop();
    std::cout << "After 2 pops:\n";
    std::cout << "deqQueue front and back: " << deqQueue.front() << ", " << deqQueue.back() << std::endl;
    std::cout << "lisQueue front and back: " << lisQueue.front() << ", " << lisQueue.back() << std::endl;
    printDeqQueue(deqQueue);
    printLisQueue(lisQueue);

    // size - gives the size of the queue
    std::cout << "Size of deqQueue: " << deqQueue.size() << std::endl;
    std::cout << "Size of lisQueue: " << lisQueue.size() << std::endl;   
    */

    // emplace functions take an array of arguments and pass it to the object's class constructor which is then invoked
    // insert function requires an already constructed object as its argument, and as a result, a copy constructor is invoked during insertion
    // demonstrating emplace in std::queue
    std::queue<A> q;

    std::cout << "construct objects of A 3 times:\n";
    A one("one");
    A two{"two"};
    A three;

    std::cout << "insert:\n";
    A zero("zero");
    q.push(zero);

    std::cout << "emplace:\n";
    q.emplace("four");

    return 0;
}