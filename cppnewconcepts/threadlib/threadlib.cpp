// std::thread library in CPP
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>

/*
    IMPORTANT LINKS:
    https://stackoverflow.com/questions/31978324/what-exactly-is-stdatomic (STD::ATOMIC AND ITS SIGNIFICANCE)   
*/

// threads are the smallest unit of execution in a program. they allow multiple functions to run concurrently
// the std::thread library in C++ provides a mechanism for creating and managing concurrent execution threads

// the thread object can be provided a function as an argument directly which it would execute as a part of its execution

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

// when we run many threads, what we can observe is that the printing to screen operation
// takes place in a random manner, in other words - there is no monitoring as to which thread uses the output console at what time
// in order to control this, we make use of mutex (mutually exclusive) locks - which help a thread which has that lock hold on to a certain
// resource until it lets go of the mutex lock, after which it is available for the other threads.
std::mutex stdoutLock;

// the mutex header provides various kinds of mutex locks to work with, which are: mutex, timed_mutex (implements locking with timeout), 
// recursive_mutex (can be locked recursively by the same thread), etc.
// each mutex provides three basic functions - lock, unlock and try_lock (which tries to lock the mutex, and returns when the mutex is not available)

// having to lock before doing the entire job, and then releasing it after the job is done, is essentially making the multithreaded
// application run in a serial manner which is not what is desired in a multithreaded application
// also known as "big lock"

// conditional variables are a synchronisation primitive which is used to block one or more threads until another thread, modifies the shared
// variable and notifies the conditional_variable - notify_one or notify_all
std::condition_variable sharedCondVar;

// std::atomic is designed to facilitate atomic operations on shared variables ensuring that operations on these variables 
// are performed indivisibly, without interference from other threads.
// atomic variables also eliminate the need for locks, since they are implemented using atomic CPU instructions (hardware-oriented)
// it also allows us to specify ceratin memory ordering constraints - which determines the memory access order of threads in atomic operations
static std::atomic<int> sharedVarAtom;

// creating a more granular multithreaded application by providing lock and unlock operations before each and every 
// resource access (in this case printing to the console) - runs in parallel manner
void threadFunc(int tid) {
    stdoutLock.lock();
    std::cout << "Thread #" << tid << " starting.\n";
    stdoutLock.unlock();

    for(int i=0; i < 20; i++) {
        stdoutLock.lock();
        std::cout << "Thread #" << tid << " running, i = " << i << std::endl;
        stdoutLock.unlock();
    }
    
    stdoutLock.lock();
    std::cout << "Thread #" << tid << " finished.\n";
    stdoutLock.unlock();
}

// race problem - a data race occurs in a concurrent program when two or more threads access shared data concurrently, and at least one of
// those accesses is a write operation, without proper synchronization. When such a scenario happens, the outcome of the program becomes 
// dependent on the non-deterministic ordering of instructions executed by the threads, leading to unpredictable behavior and incorrect results.
static int sharedValue = 0;

// we use std::mutex to fix this race problem - due to this we are able to get the desired value for the shared variable without any unpredictability
// (also called a binary semaphore)
std::mutex sharedValLock;

void sharedValueManipulator(int tid) {

    // sometimes the programmer might forget to unlock a certain mutex lock which they had acquired previously, resulting in deadlock
    // to avoid having to manually lock and unlock the mutex, we make use of std::lock_guard, which provides a convenient wrapper which acquires
    // a mutex lock upon construction, and releases it immediately upon destruction (going out of scope) - ensures that the mutex is always released
    // follows the RAII principle, which helps in preventing deadlocks and memory leaks
    // std::lock_guard<std::mutex> sharedGuard(sharedValLock);

    // sharedValLock.lock();
    // sharedValue = sharedValue + 1;
    sharedVarAtom++;
    std::cout << "Thread #" << tid << " running" << std::endl;
    // if we do not unlock this lock, then deadlocked state - execution does not proceed as all threads are blocked 
    // sharedValLock.unlock();
}

int main() {
    using namespace std::literals::chrono_literals;

    std::cout << "Number of concurrent threads supported: " << std::thread::hardware_concurrency() << std::endl;

    /*
    std::thread first(firstFunc);
    std::thread second(secondFunc);
    std::thread third(thirdFunc);

    // each thread has the get_id() function that uniquely identifies the current running thread
    std::cout << "thread IDs of the threads: " << std::endl;
    std::cout << "first thread: " << first.get_id() << std::endl;
    std::cout << "second thread: " << second.get_id() << std::endl;
    std::cout << "third thread: " << third.get_id() << std::endl;

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

    // when you call the join method, you are saying that you want to wait for this thread to finish its execution before continuing
    // with the current thread, and the calling thread (usually main) will be blocked until the thread completes execution
    // using this ensures that all threads complete their tasks before the program exits, preventing resource leaks or undefined behaviour
    first.join();
    second.join();

    // when you call the detach method, you are relinquishing the ownership of that thread to the system, and the detached thread will 
    // continue to execute independently in the background without any association with the std::thread object from which it was detached.
    // the calling thread can continue its execution without having to wait for the detached thread to finish
    // after detachment, the object becomes non-joinable, and the ability to manipulate it directly is lost
    third.detach();

    // passing lambda functions to thread objects
    auto lambda = [](int x) { 
        while(x < 10) {
            std::this_thread::sleep_for(0.5s);
            std::cout << x << "\n";
            x++;
        }
    };

    std::thread lmdThread(lambda, -10);
    lmdThread.join();
    
    std::cout << "Main thread finished.\n";

    // creating a vector of thread pointers
    std::vector<std::thread*> threads;
    int n = 3;

    // each thread pointer is made to point to a thread created dynamically 
    for(int i=0; i<n; i++) {
        threads.push_back(new std::thread(threadFunc, i));
    }

    // each thread is now joined to the main thread and waited for the completion of its execution
    // before deleting it manually and freeing the thread pointer
    for(int i=0; i<n; i++) {    
        threads.at(i)->join();
        // removing only the thread object (from the heap) which is pointed by the thread pointer --- the thread pointer still remains in the vector!
        delete threads.at(i);
    }

    // note that once main function finishes, the vector of threads will also be de-allocated
    // we make sure we do not leave out any memory leaks by de-allocating those thread pointers whose thread execution has finished

    // creating a vector of threads to check how they manipulate a common shared value
    std::vector<std::thread> threads;

    for(int i=0; i<10; i++) {
        threads.push_back(std::thread(sharedValueManipulator, i));
    }    

    for(int i=0; i<10; i++) {
        threads[i].join();
    }    

    std::cout<< "Shared value: " << sharedVarAtom << std::endl;

    bool notified = false;

    std::thread reporter([&] {
        std::unique_lock<std::mutex> lock(sharedValLock);
        if(!notified) {
            sharedCondVar.wait(lock);
        }
        std::cout << "Shared value: " << sharedValue << std::endl;
    });

    std::thread worker([&] {
        using namespace std::literals::chrono_literals;
        std::unique_lock<std::mutex> lock(sharedValLock);
        sharedValue = 12345;
        notified = true;
        std::this_thread::sleep_for(1s);
        sharedCondVar.notify_one();
    });

    reporter.join();
    worker.join();
    */

    return 0;
}