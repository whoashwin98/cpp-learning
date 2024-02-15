// erase remove idiom in CPP
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

// erase-remove idiom is a C++ programming technique, which is used for removing elements from a container based on a certain value or condition
// it involves two steps primarily: using std::remove or std::remove_if to remove the required elements, and then calling the erase member function

// std::remove - removes all elements which are equal to the specified value, in the given range [first, last) and returns a new past-the-end iterator
// which points to the element next to the end of the new list (of unremoved elements)

// std::remove_if - removes all elements which satisfy the given predicate, in the given range [first, last) and returns a new past-the-end iterator
// which points to the element next to the end of the new list (of unremoved elments)

// normally, the erase member function is used to remove element(s) from a container or collection. but, for an array-based collection like vector, 
// after an element has been deleted, all the elements after it have to be shifted forward (to fill the gaps) - causes overhead for large-sized containers
// the remove and remove_if methods work by moving the elements that do not satisfy the condition to the front, while preserving the original order
// this is because they work using two forward iterators, and have no idea about the type of the underlying container
// now, these operations return a past-the-end iterator (say 'it'), which would be pointing to the first element out of the collection of elements 
// we wish to remove from the container. so now, we can call the erase method on the range (it to container.end()) which would now be a simple
// deletion without having to move elements to fill gaps

void printVec(std::vector<int>& vec) {
    for(auto num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void printVec(std::list<int>& vec) {
    for(auto num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> vec{1,2,3,3,4,4,4,5,6,6,6,6,7,7,8,8,9,10,10};
    // std::list<int> vec{1,2,3,3,4,4,4,5,6,6,6,6,7,7,8,8,9,10,10};

    std::cout << "Original vector: ";
    printVec(vec);

    auto iter = std::remove(vec.begin(), vec.end(), 6);

    std::cout << "Vector after using std::remove: ";
    printVec(vec);

    vec.erase(iter, vec.end());
    std::cout << "Vector after using erase from iter to end: ";
    printVec(vec);

    iter = std::remove_if(vec.begin(), vec.end(), [](int x){ return x > 5; });
    std::cout << "Vector after using std::remove_if: ";
    printVec(vec);

    vec.erase(iter, vec.end());
    std::cout << "Vector after using erase from iter to end: ";
    printVec(vec);

    std::vector<int> removed(vec.size());
    iter = std::remove_copy(vec.begin(), vec.end(), removed.begin(), 4);
    std::cout << "Vector after using std::remove_copy: ";
    printVec(vec);
    // we can use move assignment to save copying overhead
    vec = std::move(removed);
    vec.erase(iter, vec.end());
    std::cout << "Vector after using erase from iter to end: ";
    printVec(vec);

    return 0;
}