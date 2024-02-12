// std::thread library in CPP
#include <iostream>
#include <thread>


// threads are the smallest unit of execution in a program. they allow multiple functions to run concurrently
// the std::thread library in C++ provides a mechanism for creating and managing concurrent execution threads

// the thread object can be provided a function as an argument directly which it would execute as a part of its execution

static bool firstFinished  = false;
void firstFunc() {
    using namespace std::literals::chrono_literals;
    while(!firstFinished) {
        std::cout << "First thread ID: " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(1s);
    }
}

static bool secondFinished = false;
void secondFunc() {
    using namespace std::literals::chrono_literals;
    while(!secondFinished) {
        std::cout << "Second thread ID: " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(1s);
    }
}

static bool thirdFinished = false;
void thirdFunc() {
    using namespace std::literals::chrono_literals;
    while(!thirdFinished) {
        std::cout << "Third thread ID: " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(1s);
    }
}

int main() {
    std::thread first(firstFunc);
    std::thread second(secondFunc);
    std::thread third(thirdFunc);

    std::cout << "are the three threads joinable?: " << std::endl;
    std::cout << "first thread: " << first.joinable() << std::endl;
    std::cout << "second thread: " << second.joinable() << std::endl;
    std::cout << "third thread: " << third.joinable() << std::endl;

    std::cin.get();
    firstFinished = true;
    std::cin.get();
    secondFinished = true;
    std::cin.get();
    thirdFinished = true;

    // the join method is used to wait for a thread to finish is execution before proceeding
    first.join();
    second.join();

    // the detach method allows a thread to run independently
    third.detach();

    // each thread has the get_id() function that uniquely identifies the current running thread
    std::cout << "Finished.\n";

    return 0;
}