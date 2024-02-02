// span STL in CPP
#include <iostream>
#include <array>
#include <span>
#include <vector>

/*
    IMPORTANT LINKS:
    https://stackoverflow.com/questions/45723819/what-is-a-span-and-when-should-i-use-one
*/

// span describes an object which can refer to a contiguous sequence of objects
// it can have a static extent or dynamic extent
// if it has static extent, its size is known at compile time itself, and it holds only the pointer to the base address of the container being referred
// if it has dynamic extent, it holds both a pointer to the container as well as the size
// includes functionalities like bounds checking, and is lightweight

// it basically serves the same purpose as string_view does for string - provide a read-only view of the data structure, thus avoiding unnecessary
// copying (when containers are passed to functions) and improving performance
// in other words, it is a non-owning type (reference type) - never allocates or deallocates anything

// note that a span has stricter requirements than an iterator pair - element contiguity and presence of elements in memory
// do not use them as a replacement for containers which are fit for your purpose

// passing argument by a non-const reference pretty much indicates “this argument will be changed by this function”
// const reference is used to pass big structures without copying them

// key advantage is the ability to work with sequential data structures without having to copy or transfer ownership

// copy of arr is created for the function here
void printArray(int* arr, int size) {
    for(int i=0; i<size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// here a view of the passed contiguous data structure is provided
// we can modify the value of the data structure unlike std::string_view
void printArr(std::span<int> arr) {
    for(auto& elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main() {
    int arr[] = {1,2,3,4};
    printArray(arr, 4);

    // can pass std::array into a function containing std::span as argument
    std::array<int, 4> a{5,6,7,8};
    printArr(a);

    // can also pass std::vector into a function containing std::span as argument
    std::vector<int> vec{11,22,33,44};
    printArr(vec);
    return 0;
}