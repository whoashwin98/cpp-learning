// priority_queue STL in CPP
#include <iostream>
#include <queue>
#include <vector>
#include <deque>

// priority_queue is a container adaptor that provides constant lookup time for the largest (by default) element, and logarithmic insertion and extraction
// we can provide a custom comparator function which would change the ordering (std::greater<int> would make smallest element to appear at the top)
// it is similar to working with heap in some random access container - with the power of not being to invalidate the heap
// the underlying container is std::vector by default, but any container which provides random access, and is a SequenceContainer can be used
// the containers which can be used as an underlying container are: std::vector and std::queue

// internally, to maintain the heap order, it makes use of the std::make_heap function - takes in a range and a comparator and creates a heap

// useful in cases where we need to process elements in the order in which they arrive, but on a priority-based approach
// algorithms like Dijkstra's use this to find the shortest path from source to destnation in a graph, and a task scheduler where tasks
// with higher priority need to be executed first

struct A {
    std::string s;
    A(const std::string& str) : s(std::move(str)) { std::cout << " constructed\n"; }
    A(const A& o) : s(o.s) { std::cout << " copy constructed\n"; }
};

struct comp {
    bool operator()(const A& a1, const A& a2) const {
        return a1.s < a2.s;
    }
};

int main() {
    /*
    std::vector<int> nums;
    for(int i=1; i<=10; i++) nums.push_back(i);

    // default behaviour - std::vector as the underlying container with the largest element at the top
    std::priority_queue<int> maxHeap;
    // to create a min-heap, we specify std:greater<int> as the comparator
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

    // push - inserts an element into the priority queue
    // note that here the insertion operation is not constant-time 
    // it takes logarithmic time for comparison, plus the complexity of the underlying container's push function
    for(int num : nums) maxHeap.push(num);
    for(int num : nums) minHeap.push(num);

    // top - returns the current highest priority element in the PQ
    std::cout << "Current top of maxHeap PQ: " << maxHeap.top() << std::endl;
    std::cout << "Current top of minHeap PQ: " << minHeap.top() << std::endl;

    // pop - removes the highest priority element from the PQ
    // it takes logarithmic time for comparison, plus the complexity of the underlying container's pop function
    std::cout << "Removing the top 3 maximum elements..." << std::endl;
    maxHeap.pop();  maxHeap.pop();  maxHeap.pop();
    std::cout << "New top of maxHeap PQ: " << maxHeap.top() << std::endl;
    
    std::cout << "Removing the top 3 minimum elements..." << std::endl;
    minHeap.pop();  minHeap.pop();  minHeap.pop();
    std::cout << "New top of minHeap PQ: " << minHeap.top() << std::endl;

    // size - checks the current size of the priority queue
    std::cout << "Size of maxHeap PQ: " << maxHeap.size() << std::endl;
    std::cout << "Size of minHeap PQ: " << minHeap.size() << std::endl;
    */

    // emplace functions take an array of arguments and pass it to the object's class constructor which is then invoked
    // insert function requires an already constructed object as its argument, and as a result, a copy constructor is invoked during insertion
    // demonstrating emplace in std::queue
    std::priority_queue<A, std::vector<A>, comp> pq;

    std::cout << "construct objects of A 2 times:\n";
    A one("one");
    A two{"two"};

    std::cout << "insert:\n";
    A zero("zero");
    pq.push(zero);

    std::cout << "emplace:\n";
    pq.emplace("four");
    
    return 0;
}