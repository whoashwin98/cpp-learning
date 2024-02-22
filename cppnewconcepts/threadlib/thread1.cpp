// basics of std::thread library in CPP
#include <iostream>
#include <thread>

// a thread is the smallest unit of execution in a program (lightweight process), allow multiple functions to run concurrently.
// it is a wrap-around (opaque identifier) to the system thread and it provides a platform-independent interface to thread operations
// the thread object can be provided a function as an argument directly which it would execute as a part of its execution

// an example function which can be run by a std::thread object
void doTask(int x) {
    std::cout << "Thread owned by object 't' running...\n";
    using namespace std::literals::chrono_literals;
    int i=0; 
    while(i < x) {
        std::cout << "Value printed: " << i << "\n";
        i++;
        std::this_thread::sleep_for(0.1s);
    }
}

int main() {

    // as soon as this thread object is created, the execution starts
    std::thread t(doTask, 10);

    // when you call the join method, you are saying that you want to wait for this thread to finish its execution before continuing
    // with the current thread, and the calling thread (usually main) will be blocked until the thread completes execution
    // using this ensures that all threads complete their tasks before the program exits, preventing resource leaks or undefined behaviour
    t.join();

    // when you call the detach method, you are relinquishing the ownership of that thread to the system, and the detached thread will 
    // continue to execute independently in the background without any association with the std::thread object from which it was detached.
    // the calling thread can continue its execution without having to wait for the detached thread to finish
    // after detachment, the object becomes non-joinable, and the ability to manipulate it directly is lost
    //t.detach();

    // implementing the doTask function as a lambda in order to pass it as an argument to the thread constructor
    std::thread t2([](int x){
        std::cout << "Thread owned by object 't2' running...\n";
        using namespace std::literals::chrono_literals;
        int i=0; 
        while(i < x) {
            std::cout << "Value printed: " << i << "\n";
            i++;
            std::this_thread::sleep_for(0.1s);
        }
    }, 10);

    t2.join();

    std::cout << "Main thread finished.\n";

    return 0;
}