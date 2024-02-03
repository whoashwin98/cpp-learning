// vector STL in CPP
#include <iostream>
#include <string>
#include <vector>

// vectors are sequential containers which contain elements in contiguous fashion and can change in size
// their storage is handled by the compiler
// they occupy more space than static arrays because they need room for expansion (more memory allocated)
// they provide random access, insert and delete in constant time (end) and linear time (anywhere else)

// meets the requirements of Container, ReversibleContainer, SequenceContainer
// Container - an object used to store other objects and taking care of the memory used by the containing objects
// ReversibleContainer - a Container that has iterators which allow it to be iterated in a reverse fashion
// SequenceContainer - a Container that store objects of the same type in a linear arrangement

void printArray(int* arr, int size) {
    for(int i=0; i<size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void printVector(std::vector<int>& arr) {
    for(auto ele : arr) {
        std::cout << ele << " ";
    }
    std::cout << std::endl;
}

struct A {
    std::string s;
    A(std::string str) : s(std::move(str)) { std::cout << " constructed\n"; }
    A(const A& o) : s(o.s) { std::cout << " copy constructed\n"; }
    A(A&& o) : s(std::move(o.s)) { std::cout << " move constructed\n"; }
    A& operator=(const A& other)
    {
        s = other.s;
        std::cout << " copy assigned\n";
        return *this;
    }
    A& operator=(A&& other)
    {
        s = std::move(other.s);
        std::cout << " move assigned\n";
        return *this;
    }
};

int main() {
    /*
    // initialising a vector
    std::vector<int> v0;
    std::vector<int> v1 = {10, 11, 12};
    std::vector<int> v2(5,5);
    
    // creating a vector from a C-style array
    int arr[] = {5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    std::vector<int> v3(arr, arr+n);

    // creating a vector using fill function
    std::vector<int> v4(10);
    fill(v4.begin(), v4.end(), 7);


    std::vector<int> vec{1,2,3,4,5,6,7,8,9};
    for(auto ele : vec) {
        std::cout << ele << " ";
    }
    std::cout << std::endl;

    // element access - at() function (bound checks done) - linear time
    std::cout << "Element at position 6 is: " << vec.at(6) << std::endl;
    // throws an out_of_range exception
    // std::cout << "Element at position 13 is: " << vec.at(13) << std::endl;

    // element access using the [] operator
    std::cout << "Element at position 4 is: " << vec[3] << std::endl;
    // allows to go out of range and modify - UNDEFINED BEHAVIOUR
    // std::cout << "Element at position 13 is: " << vec[12] << std::endl;     // prints garbage value when not modified
    // vec[12] = 1234;                                                         // segmentation fault 11 - program trying to access invalid memory location
    // std::cout << "Element at position 13 is: " << vec[12] << std::endl;     // after modification the assigned value is printed


    // front() and back() return the first and last element respectively
    std::cout << "First element: " << vec.front() << std::endl;
    std::cout << "Last element: " << vec.back() << std::endl;

    // get a C-style pointer to work with legacy code
    printArray(vec.data(), vec.size());

    // iterators - normal iterators
    std::cout << "Printing vector elements using normal iterators:\n"; 
    for(auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // iterators - reverse iterators (print in reverse)
    std::cout << "Printing vector elements using reverse iterators:\n";
    for(auto it = vec.rbegin(); it != vec.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // checking the capacity of vector
    std::cout << "Size of the vector: " << vec.size() << std::endl;
    vec.push_back(10);      // capacity of the vector doubles
    
    // every time we keep inserting elements and when the capacity is reached, elements are copied 
    std::cout << "Capacity of the vector: " << vec.capacity() << std::endl; 
    vec.pop_back();
    
    // to make things faster, we can set the capacity of a vector initially by using the reserve method
    // if the number specified is less than the current capacity then no change is made
    vec.reserve(50);
    std::cout << "Capacity of the vector after reserve(): " << vec.capacity() << std::endl; 

    // shrink_to_fit drops the unused memory and makes the capacity equal to the current size
    vec.shrink_to_fit();
    std::cout << "Size of the vector: " << vec.size() << std::endl;   
    std::cout << "Capacity of the vector after shrink_to_fit(): " << vec.capacity() << std::endl; 
    */

    // modifying the vector and its elements
    std::vector<int> vec{1,2,3,4,5,6,7,8,9};
    vec[5] = 50;
    
    // push_back inserts element at the end of the vector
    vec.push_back(10);
    std::cout << "After push_back: ";
    printVector(vec);

    // insert inserts the element at the desired position
    // all insertions happen in linear time - elements after the one inserted are shifted to make space for the new element
    vec.insert(vec.begin(), 0);     // insert 1 element at specified position
    std::cout << "After inserting 1 element: ";
    printVector(vec);               
    vec.insert(vec.begin() + 2, 3, 777);    // insert 3 elements at specified position
    std::cout << "After inserting 3 elements: ";
    printVector(vec);

    // we can also insert elements from another vector or C-style array
    std::vector<int> v{501, 502};
    vec.insert(vec.begin() + 6, v.begin(), v.end());
    std::cout << "After inserting from another vector: ";
    printVector(vec);
    
    int arr[] = {301, 302, 303, 304};
    vec.insert(vec.end(), arr, arr+std::size(arr));
    std::cout << "After inserting from another array: ";
    printVector(vec);

    // pop_back is used to remove element from the end
    vec.pop_back();
    std::cout << "After pop_back: ";
    printVector(vec);

    // erase method is used to erase one element or a range of elements
    // linear time is taken - since remaining elements need to be shifted after removal
    vec.erase(vec.begin() + 6);     // erase one elememt
    std::cout << "After erasing 4th element: ";
    printVector(vec);

    vec.erase(vec.begin() + 2, vec.begin() + 5);    // erase a range of elements
    std::cout << "After erasing 3 elements from positions 2 to 5: ";
    printVector(vec);

    // clear is used to erase all the elements in the array and make it empty
    vec.clear();
    std::cout << "After clear(): ";
    printVector(vec);
    
    // emplace is used to insert elements in-place without having to create a copy of the object
    // this is especially useful in cases where we create a vector of objects - efficiency is improved

    // the main difference between insert and emplace is that: 
    // for insert we need to pass an already constructed object for it to be inserted to the container
    // for emplace, we can pass the arguments for the constructor to it for it to construct an object and insert it
    // in both cases, the type of constructor run is different (copy and parameterised respectively)
    /*
    std::vector<A> container;
    container.reserve(10);

    std::cout << "construct A 3 times:\n";
    A two { "two" };
    A three { "three" };
    A zero("zero");

    std::cout << "insert:\n";
    container.insert(container.begin(), zero);

    std::cout << "emplace:\n";
    container.emplace(container.end(), "one");
 
    std::cout << "emplace with A&:\n";
    container.emplace(container.end(), two);
 
    std::cout << "emplace with A&&:\n";
    container.emplace(container.end(), std::move(three));
    */

    // multidimensional vectors
    std::cout << "matrix contents: " << std::endl;
    std::vector<std::vector<int>> mat{{1,2,3},{4,5,6},{7,8,9}};
    for(int i=0; i<mat.size(); i++) {
        for(int j=0; j<mat[0].size(); j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}