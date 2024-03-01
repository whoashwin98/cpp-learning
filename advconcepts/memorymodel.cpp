// memory model in CPP
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

// memory model is a specification that describes how a program interacts with the memory. 
// C++11 provided a standardised memory model to address issues related to concurrency, ordering and multithreading.
// the main features of the memory model are described below: 

// 1. atomic operations: these are indivisible operations which are used to prevent data races in multi-threaded applications. 
// the "std::atomic" template encapsulates a variable that can be accessed and modified atomically. It ensures that read-modify-write 
// operations on the variable are performed atomically, without interruption from other threads.
// using a normal static variable leads to unwanted results 
// static int shared = 0;
// using a std::atomic variable 
std::atomic<int> shared(0);
void incrementShared() {
    // shared = shared + 1;
    // need to give an atomic operation like ++, +=, etc. 
    shared += 1;
}


// 2. memory order: these memory order properties specify how memory access should be ordered and synchronised in multi-threaded environments
// used with atomic operations to control the visibility and ordering of memory access between threads. several memory order properties have been
// specified by C++ for the atomic operations like 'load', 'store' and 'exchange'. 

// a. memory_order_relaxed: this provides the least amount of synchronisation, as it allows reordering of memory accesses and does not guarantee sync.
// between multiple threads, but it ensures atomicity of the operation being performed.
/*
std::atomic<int> test(0);
void storeTest() {
    test.store(3, std::memory_order_relaxed);
}
void loadTest() {
    int localTest = test.load(std::memory_order_relaxed);
    std::cout << "Locally loaded test = " << localTest << std::endl;
}
*/

// b. memory_order_acquire: this memory order ensures that all memory accesses performed after the atomic operation are visible to the current thread. 
// it prevents reads and writes before the atomic operation from being reordered after it.
// c. memory_order_release: this memory order ensures that all memory accesses performed before the atomic operation are visible to other threads. 
// it prevents reads and writes after the atomic operation from being reordered before it.
/*
std::atomic<int> test(0);
void storeTest() {
    test.store(3, std::memory_order_release);
}
void loadTest() {
    int localTest = test.load(std::memory_order_acquire);
    std::cout << "Locally loaded test = " << localTest << std::endl;
}
*/

// memory_order_seq_cst (sequential consistency): this memory order provides the strongest synchronization guarantees. 
// it ensures that all threads observe a consistent order of memory accesses as if they occurred in a single, total order. 
// it imposes the most strict ordering requirements and typically incurs more overhead compared to other memory orders.

std::atomic<int> test(0);
void storeTest() {
    test.store(3, std::memory_order_seq_cst);
}
void loadTest() {
    int localTest = test.load(std::memory_order_seq_cst);
    std::cout << "Locally loaded test = " << localTest << std::endl;
}


int main() {
    /*
    std::vector<std::thread> threads;
    int n = 1000;
    for(int i=0; i<n; i++) threads.push_back(std::thread(incrementShared));
    for(int i=0; i<n; i++) threads[i].join();
    std::cout << "Shared value: " << shared << std::endl;
    */

    std::thread t1(storeTest);
    std::thread t2(loadTest);

    t1.join();
    t2.join(); 

    return 0;
}
