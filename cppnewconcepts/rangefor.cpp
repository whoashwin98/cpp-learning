// range-based for loops in CPP
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

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
        std::cout << *it << " ";
        // since there is access to iterators here directly, manipulating them would lead to unexpected errors
    }
    std::cout << std::endl;


    // range-based for loops don't provide any opening for doing any invalidation or miscalculations
    // range-based for loop internally handles any changes to the container's size or memory layout - if any changes made in loop
    for(auto elem : vec) {
        // trying to modify the container inside the range-based for loop - leads to iterator invalidation and undefined behaviour
        vec.push_back(333);
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // printing the vector again - this time, the elements inserted during the previous range-based for loop is now visible
    for(auto elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // trying range-based for loops for iterating through different STL containers

    // range-based for loop works for traditional C-style arrays
    int arr[] = {1,2,3,4,5,6,7};
    for(auto elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // trying range-based for loops on other containers : list, deque, set, unordered_set, map, unordered_map
    std::string str{"hello world"};
    std::list<int> lis{1,2,3,4,5};
    std::deque<int> dq{1,2,3,4,5,6,7,8};
    std::set<int> s{1,2,3,4,5};
    std::unordered_set<int> us{1,2,3};
    std::map<std::string, int> mp{{"first", 1}, {"second", 2}, {"third", 3}};
    std::unordered_map<std::string, int> ump{{"first", 1}, {"second", 2}, {"third", 3}, {"tenth", 10}};

    for(auto ch : str) { std::cout << ch << " "; }
    std::cout << std::endl;

    for(auto elem : lis) { std::cout << elem << " "; }
    std::cout << std::endl;
    
    for(auto elem : dq) { std::cout << elem << " "; }
    std::cout << std::endl;
    
    for(auto elem : s) { std::cout << elem << " "; }
    std::cout << std::endl;
    
    for(auto elem : us) { std::cout << elem << " "; }
    std::cout << std::endl;
    
    for(auto [key, value] : mp) { std::cout << key << "$" << value << " "; }
    std::cout << std::endl;

    for(auto [key, value] : ump) { std::cout << key << "$" << value << " "; }
    std::cout << std::endl;
    
    return 0;
}