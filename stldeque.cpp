// deque STL in CPP
#include <iostream>
#include <deque>
#include <algorithm>
#include <string>

/*
    IMPORTANT LINKS:
    https://chat.openai.com/c/1f04c805-3a88-4990-a06d-3770d7daeba2 (DEQUE INTERNAL IMPLEMENTATION)
    https://cengizhanvarli.medium.com/when-should-we-std-deque-instead-of-std-vector-97971028764e (DEQUE VS. VECTOR)
*/

// deque - an indexed sequence container that allows fast insertion and deletion from both ends (stands for double-ended queue)
// similar to the vector data structure - but limited as it allows insertion and deletion from both the ends only

// random access possible - because of a combination of indexing and pointer arithmetic with the blocks that make up the deque's internal structure
// though it doesn't have contiguous storage like the std::vector, it provides faster random access due to its block-based design
// reason - deque is made up of a series of blocks where each block is itself a dynamic array. when an element is randomly accessed, 
// it involves first indexing into a block, and then performing pointer arithmetic in the dynamic array that is pointed by that block to get to
// the element we are looking for. since blocks are smaller in size and more localised, finding elements for random access becomes easier
// when compared to vectors.

// note that the elements in deque are not stored contiguously, rather stored as an array of pointers to memory blocks
// which in turn contain the elements of the deque. (double dereferencing required when random access is done)
// this can be thought of as a linked list of vectors
// for allocating a new block of memory, it first determines whether there is any space remaining at the front of the list in current memory block
// this makes expansion and contraction of deques much cheaper than vectors (which require copying elements to new locations)

// provides constant time access as well as constant time insertion and removal at the ends, but linear time removal of middle elements

// insertion or deletion when performed at the middle, leads to iterator invalidation
// rest of the methods which perform operations at the ends of the deque do not invalidate any iterators

void printDeque(std::deque<int>& dq) {
    for(auto it : dq) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}

struct A {
    std::string s;
    A(std::string str) : s(std::move(str)) { std::cout << " constructed\n"; }
    A(const A& o) : s(o.s) { std::cout << " copy constructed\n"; }
};

int main() {
    /*
    
    std::deque<int> dq{1,2,3,4,5,6,7,8};

    // random access of elements
    // [] operator does not perform any kind of bound checking
    std::cout << "3rd element in the deque: " << dq[2] << std::endl;
    // at() method performs bound checking, and returns out_of_range error if encountered
    std::cout << "5th element in the deque: " << dq.at(4) << std::endl;
    // front and back of the deque 
    std::cout << "Front element: " << dq.front() << std::endl;
    std::cout << "Back element: " << dq.back() << std::endl;

    // iterators and reverse iterators both are available
    std::cout << "Contents of deque: ";
    for(auto it = dq.begin(); it != dq.end(); it++) {
       std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Contents of deque in reverse order: ";
    for(auto it = dq.rbegin(); it != dq.rend(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // functions to know the size and capacity of the deque
    std::cout << "Size of the deque is: " << dq.size() << std::endl;
    std::cout << "Maximum possible size of the deque is: " << dq.max_size() << std::endl;

    // push_front - insert an element in the front of the deque
    dq.push_front(0);
    std::cout << "After push_front: ";
    printDeque(dq);

    // push_back - insert an element at the end of the deque
    dq.push_back(9);
    std::cout << "After push_back: ";
    printDeque(dq);

    // insert - insert element(s) at specified position
    dq.insert(dq.begin() + 2, 777);
    std::cout << "After inserting one element at pos: ";
    printDeque(dq);

    dq.insert(dq.end() - 2, 4, 100);
    std::cout << "After inserting 4 duplicate elements at pos: ";
    printDeque(dq);

    int arr[] = {501, 502, 503, 504, 505, 506};
    dq.insert(dq.begin() + 5, arr, arr + std::size(arr));
    std::cout << "After inserting elements from an array: ";
    printDeque(dq);

    // pop_front - removes an element from the front of the deque
    dq.pop_front();
    std::cout << "After pop_front: ";
    printDeque(dq);

    // pop_back - removes an element from the back of the deque
    dq.pop_back();
    std::cout << "After pop_back: ";
    printDeque(dq);

    // erase - used to remove element or a range of elements from the deque
    // linear complexity in erasing the elements
    dq.erase(dq.begin() + 1);
    std::cout << "After erasing one element from the middle: ";
    printDeque(dq);

    dq.erase(dq.begin() + 3, dq.begin() + 9);
    std::cout << "After erasing a range of elements: ";
    printDeque(dq);

    // resize - increase or decrease the size of the deque
    // performs in linear time of abs(new size - current size). note that on decreasing and then increasing the size, data is lost
    // decreasing the size 
    dq.resize(3);
    std::cout << "After resizing to 3 elements: ";
    printDeque(dq);

    // increasing the size;
    dq.resize(7, -4);
    std::cout << "After resizing to 7 elements: ";
    printDeque(dq);
    */

    // emplace, emplace_front and emplace_back serve the same purpose - prevent object copying at the time of insertion
    // emplace functions take an array of arguments and pass it to the object's class constructor which is then invoked
    // insert function requires an already constructed object as its argument, and as a result, a copy constructor is invoked during insertion
    std::deque<A> container;
    
    std::cout << "construct 2 times A:\n";
    A three { "three" };
    A four { "four" };
    
    std::cout << "insert:\n";
    A one("one");
    container.insert(container.begin(), one);

    std::cout << "emplace:\n";
    container.emplace(container.end(), "two");

    std::cout << "emplace_front:\n";
    container.emplace_front("zero");

    std::cout << "emplace_back:\n";
    container.emplace_back("five");

    return 0;
}