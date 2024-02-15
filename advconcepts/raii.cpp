// RAII concept in CPP
#include <iostream>

/*
    IMPORTANT LINKS: 
    https://chat.openai.com/c/c2663ec0-5083-4110-985a-eca359474b0c (RAII AND ITS IMPORTANCE)
*/

// RAII stands for Resource Acquisition Is Initialisation, which is a programming technique used to manage resources automatically
// and ensure they are properly cleaned up when they are no longer required. (core idea is to tie the lifecycle of a resource to that of object)

// basically under this principle, we encapsulate each resource into a class, where
// 1. the constructor acquires the resource and establishes all class invariants or throws an exception if that cannot be done
// 2. the destructor releases the resource and never throws exceptions

// always use the resource via an instance of this RAII class that either has automatic storage duration or temporary lifetime itself, or
// has lifetime that is bounded by the lifetime of an automatic or temporary object

// now creating a class 'Collection' in order to handle this dynamically allocated resource using the RAII technique
class Collection {
    int* data;  
    int size;   
    public: 
    Collection() {
        size = 100;
        data = new int[100];
    }

    // overloading the indexing operators
    int& operator[](std::size_t idx) {
        return data[idx];
    }

    const int& operator[](std::size_t idx) const {
        return data[idx]; 
    }

    ~Collection() {
        size = -1;
        delete[] data;
    }
};

/*
    error message for memory leak (leaks CLI command used)
    Process 27350: 191 nodes malloced for 10 KB
    Process 27350: 1 leak for 416 total leaked bytes.

    STACK OF 1 INSTANCE OF 'ROOT LEAK: <malloc in main>':
    3   dyld                                  0x1892dd0e0 start + 2360
    2   prog                                  0x1020b6f38 main + 24  raii.cpp:55
    1   libc++abi.dylib                       0x189616ec0 operator new(unsigned long) + 32
    0   libsystem_malloc.dylib                0x18949ba44 _malloc_zone_malloc_instrumented_or_legacy + 136 

        1 (416 bytes) ROOT LEAK: <malloc in main 0x12af040f0> [416]

    message after using RAII
    Process 27508: 190 nodes malloced for 10 KB
    Process 27508: 0 leaks for 0 total leaked bytes.
*/

void manipulateArray(int* arr, int size) {
    for(int i=0; i<10; i++) {
        arr[i] = i-1;
    }
}

int main() {
    /* 
    // allocating memory without using RAII technique
    int* arr = new int[100];

    try {
        for(int i=0; i<10; i++) {
            arr[i] = i+1;
        }
        manipulateArray(arr, 10);
        // exception occurs, so line after this never executed - leading to memory leak
        throw std::runtime_error("123");
        
        delete[] arr;

    } catch(const std::runtime_error& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }
    */
    Collection arr;

    try {
        for(int i=0; i<10; i++) {
            arr[i] = i+1;
        }
        // exception occurs, so line after this never executed - but this time, since we have used the RAII technique
        // the object de-allocates the heap allocated memory when it goes out of scope, thus preventing memory leaks
        throw std::runtime_error("123");
    } catch(const std::runtime_error& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }

    return 0;
}