// multiple threads and their executions in CPP
#include <iostream>
#include <thread>

static bool firstFinished  = false;
void firstFunc() {
    using namespace std::literals::chrono_literals;
    int i=0;
    while(!firstFinished) {
        std::cout << "First thread running, i = " << i << std::endl;
        i++;
        std::this_thread::sleep_for(1s);
    }
}

static bool secondFinished = false;
void secondFunc() {
    using namespace std::literals::chrono_literals;
    int i = 0;
    while(!secondFinished) {
        std::cout << "Second thread running, i = " << i << std::endl;
        i++;
        std::this_thread::sleep_for(1s);
    }
}

static bool thirdFinished = false;
void thirdFunc() {
    using namespace std::literals::chrono_literals;
    int i = 0;
    while(!thirdFinished) {
        std::cout << "Third thread running, i = " << i << std::endl;
        i++;
        std::this_thread::sleep_for(1s);
    }
}

int main() {
    // checking how joined and detached threads run simultaneously
    std::thread first(firstFunc);
    std::thread second(secondFunc);
    std::thread third(thirdFunc);

    std::cin.get();
    firstFinished = true;
    std::cin.get();
    secondFinished = true;
    std::cin.get();
    thirdFinished = true;

    // there is no control over which thread uses the output console at what time
    // thus this causes random order printing
    first.join();
    second.join();
    third.join();

    std::cout << "Main thread finished.\n";

    return 0;
}