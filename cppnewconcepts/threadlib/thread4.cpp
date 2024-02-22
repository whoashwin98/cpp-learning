// @file cv.cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

std::mutex gLock;
// conditional variables are a synchronisation primitive which is used to block one or more threads until another thread, modifies the shared
// variable and notifies the conditional_variable - notify_one or notify_all
std::condition_variable gConditionVariable;

int main(){

    int result = 0;
    bool notified = false;

    // reporting thread, must wait on work, done by the working thread
    std::thread reporter([&]{
        std::unique_lock<std::mutex> lock(gLock);
        if(!notified){
            gConditionVariable.wait(lock);
        }
        std::cout << "Reporter, result is: " << result << std::endl;
    });

    // working thread
    std::thread worker([&]{
        std::unique_lock<std::mutex> lock(gLock);
        // do our work, because we have the lock
        result = 42 + 1 + 7;
        // our work is done
        notified = true;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "Work complete\n";
        // wake up a thread, that is waiting, for some condition to be true
        gConditionVariable.notify_one();
    });

    reporter.join();
    worker.join();

    std::cout << "Program complete" << std::endl;
    return 0;
}