// range-based for loops in CPP
#include <iostream>
#include <vector>

// regular for loops require us to manage the index, which if not done properly leads to errors - it is compatible with all containers and sequences
// as long as they support random access, or provide a way to access elements using indices

// iterator based for loops use iterators instead of indices, which is somewhat similar; again might lead to errors if management is not done in proper
// manner, and is compatible with containers and sequences which provide iterator support

// range-based for loops provide a concise and readable way to iterate over the elements in a container or sequence without having to do index
// management - particularly useful when we want to perform operations on each element while iterating over them
// they provide simplicity and easy readability of code, and can iterate through any container that provides appropriate start and end iterators
// prevents indexing or one-off mistakes which might have occurred with the traditional for loops
// since these for loops iterate through the container by value, the container elements are not altered during the itereation

int main() {
    std::vector<int> vec{1,2,3,4,5,6,7,8,9,10};

    // using traditional for-loop to print elements
    // the range provided is incorrect here - unpredicatble behaviour - prints garbage elements
    for(int i=0; i<=vec.size() * 2; i++) {
        std::cout << vec[i] * 2 << " ";
    }
    std::cout << std::endl;

    // using iterators for printing elements
    for(auto it = vec.begin(); it != vec.end(); it++) {
        std::cout << *it * 2 << " ";
        // since there is access to iterators here directly, manipulating them would lead to unexpected errors
    }
    std::cout << std::endl;


    // range-based for loops don't provide any opening for doing any invalidation or miscalculations
    // range-based for loop internally handles any changes to the container's size or memory layout - if any changes made in loop
    for(auto elem : vec) {
        std::cout << elem * 2 << " ";
    }
    std::cout << std::endl;

    return 0;
}