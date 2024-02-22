// use of mutex, lock_guard and atomic variables in CPP
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

// race problem - a data race occurs in a concurrent program when two or more threads access shared data concurrently, and at least one of
// those accesses is a write operation, without proper synchronization. When such a scenario happens, the outcome of the program becomes 
// dependent on the non-deterministic ordering of instructions executed by the threads, leading to unpredictable behavior and incorrect results.
static int shared_value= 0;

// we use std::mutex to fix this race problem - due to this we are able to get the desired value for the shared variable without any unpredictability
// (also called a binary semaphore)

// the mutex header provides various kinds of mutex locks to work with, which are: mutex, timed_mutex (implements locking with timeout), 
// recursive_mutex (can be locked recursively by the same thread), etc.
// each mutex provides three basic functions - lock, unlock and try_lock (which tries to lock the mutex, and returns when the mutex is not available)

// having to lock before doing the entire job, and then releasing it after the job is done, is essentially making the multithreaded
// application run in a serial manner which is not what is desired in a multithreaded application
// also known as "big lock"
std::mutex gLock;

// std::atomic is designed to facilitate atomic operations on shared variables ensuring that operations on these variables 
// are performed indivisibly, without interference from other threads.
// atomic variables also eliminate the need for locks, since they are implemented using atomic CPU instructions (hardware-oriented)
// it also allows us to specify ceratin memory ordering constraints - which determines the memory access order of threads in atomic operations
static std::atomic<int> sharedVarAtom;

void shared_value_increment(){
    
    // sometimes the programmer might forget to unlock a certain mutex lock which they had acquired previously, resulting in deadlock
    // to avoid having to manually lock and unlock the mutex, we make use of std::lock_guard, which provides a convenient wrapper which acquires
    // a mutex lock upon construction, and releases it immediately upon destruction (going out of scope) - ensures that the mutex is always released
    // follows the RAII principle, which helps in preventing deadlocks and memory leaks
    // std::lock_guard<std::mutex> sharedGuard(gLock);

    // gLock.lock();
    // shared_value = shared_value + 1;
    // if we do not unlock this lock, then deadlocked state - execution does not proceed as all threads are blocked 
    // gLock.unlock();

    sharedVarAtom++;
}

int main(){

    std::vector<std::thread> threads;
    for(int i=0; i < 1000; i++){
        threads.push_back(std::thread(shared_value_increment));
    }

    for(int i=0; i < 1000; i++){
        threads[i].join(); 
    }

    // std::cout << "Shared value:" << shared_value << std::endl;
    std::cout << "Shared value:" << sharedVarAtom << std::endl;
    return 0;
}