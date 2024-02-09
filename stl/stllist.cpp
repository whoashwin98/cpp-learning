// list STL in CPP
#include <iostream>
#include <iterator>
#include <list>

/*
    IMPORTANT LINKS:
    https://chat.openai.com/c/adec07d8-8aa3-4b37-93a2-a06397fb76a7 (ITERATOR INVALIDATION + LIST ADVANTAGES & DRAWBACKS)
*/

// list - a container that supports constant time insertion and removal from anywhere in the container
// random access is not supported (implemented as a doubly linked list)
// since lists do not provide random access, their cache locality is poor as compared to arrays and vectors
// provides bidirectional access with less space efficiency - have to traverse the list in order to reach the Nth element
// inserting and deleting elements does not invalidate any pointers or iterators

// use cases of std::list is when we need to:
// 1. insert in the middle of the container 
// 2. each object must be stable in memory

// lists are rarely used from a performance standpoint, only useful when one needs to split and join to form other lists
// each element of the list has its own memory that stays valid until it is deleted - hence no need for reallocation

// iterators are used to print the list
void printList(std::list<int> l) {
    for(auto it = l.begin(); it != l.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

struct A
{
    std::string s;
    A(std::string str) : s(std::move(str)) { std::cout << " constructed\n"; }
    A(const A& o) : s(o.s) { std::cout << " copy constructed\n"; }
};

int main() {
    /*
    std::list<int> l;

    // push_front - adds an element to the front of the list
    l.push_front(1);
    std::cout << "After push_front: ";
    printList(l);

    // push_back - adds an element at the back of the list
    l.push_back(3);
    std::cout << "After push_back: ";
    printList(l);

    // insert - inserts elements at the desired position
    // note that we need to move the iterator manually to the desired position in order to be able to insert an element into it
    // the time complexity for insertion is constant, but linear (in container size) when the elements are taken from another container

    auto iter = l.begin();
    iter++;
    l.insert(iter, 2); // insert 1 element at the desired position
    std::cout << "After inserting 1 element at pos: ";
    printList(l);

    iter = l.begin();
    iter++; iter++;
    l.insert(iter, 4, 100); // insert N copies of an element at the desired position
    std::cout << "After inserting 4 copies at pos: ";
    printList(l);

    int arr[] = {301, 302, 303, 304, 305};
    int n = sizeof(arr) / sizeof(arr[0]); 
    l.insert(l.end(), arr, arr+n);  // insert an array of elements into the list (linear time in array size)
    std::cout << "After inserting arr at pos: ";
    printList(l);

    // functions to display the capacity of the list
    std::cout << "Size of the list: " << l.size() << std::endl;
    std::cout << "Maximum possible size of the list: " << l.max_size() << std::endl;

    // pop_front - removes an element from the front of the list
    l.pop_front();
    std::cout << "After pop_front: ";
    printList(l);

    // pop_back -  removes an element from the back of the list
    l.pop_back();
    std::cout << "After pop_back: ";
    printList(l);

    // erase - used to remove an element at a particular position, or a range of elements
    // time complexity is constant in erasing one element but is linear in the range when range of elements are erased
    iter = l.begin();
    std::advance(iter, 5);  // advances the specified iterator by N positions
    l.erase(iter);
    std::cout << "After erasing 1 element from pos: ";
    printList(l);

    auto i1 = l.begin(), i2 = l.begin();
    std::advance(i1, 1);
    std::advance(i2, 5);
    l.erase(i1, i2);
    std::cout << "After erasing elements from 2 to 6: ";
    printList(l);

    // clear - used to clear the entire list
    l.clear();
    std::cout << "After clear:";
    printList(l); 

    // list operations - there are various operations like merging, splicing, reversing lists, etc.
    std::list<int> l1{1,2,3,4,2,2,3,3,3,3,4,1};
    std::list<int> l2{9,5,7,6,8};

    std::cout << "Both lists originally: " << std::endl;
    printList(l1);
    printList(l2);

    // note that the std::sort function (STL algorithm) requires random access iterators to work which is not available with lists
    // the difference is that it preserves all the iterator values, and performs a stable sort
    // time complexity is approximately NLogN
    l1.sort();
    l2.sort(std::greater<int>());   // provide comparator to sort in custom order
    std::cout << "Lists after sorting: " << std::endl;
    printList(l1);
    printList(l2);
    
    // unique - removes duplicates from the list
    // no comparisons if list is empty, otherwise time taken is linear in list size (N-1 comparisons)
    // the elements which are removed, only their iterators are invalidated
    // we can also provide a custom check to filter out unique elements
    l1.unique();
    std::cout << "Lists after unique: " << std::endl;
    printList(l1);
    printList(l2);

    // reverse - reverses a list in linear time
    l2.reverse();
    std::cout << "Lists after reverse: " << std::endl;
    printList(l1);
    printList(l2);

    // merge - used to merge two SORTED lists. merges the second list into the first list
    // we can also give custom comparators to perform a customised merging (by default ascending)
    // no iterators are invalidated    
    l1.merge(l2);
    std::cout << "Lists after merge: " << std::endl;
    printList(l1); 
    printList(l2); // now l2 becomes empty

    // splice - transfers elements of one list to another list
    // performed in constant time complexity
    l2.splice(l2.begin(), l1);  // copies all elements of l1 to l2
    std::cout << "Lists after splicing: " << std::endl;
    printList(l1); 
    printList(l2);

    auto begIter = l2.begin();
    std::advance(begIter, 3);
    auto endIter = l2.begin();
    std::advance(endIter, 7); 


    // if beginning iterator is greater than the end iterator, undefined behaviour. error:
    // prog(9525,0x1df459000) malloc: *** error for object 0x16d98b2e0: pointer being freed was not allocated
    // prog(9525,0x1df459000) malloc: *** set a breakpoint in malloc_error_break to debug
    // Abort trap: 6

    // note that the last element is not included in the range!
    l1.splice(l1.begin(), l2, begIter, endIter);
    std::cout << "Lists after splicing in range: " << std::endl;
    printList(l1); 
    printList(l2);

    // remove and remove_if - used to remove elements from the list based on conditions
    // makes exactly N comparisons (N = size of list) hence linear time to run
    // do not invalidate iterators since they modify the internal pointers to skip over the elements being removed
    std::list<int> l{1, 100, 2, 3, -1, 5, 4, 1, 1, 1, 4, 3};
    std::cout << "Original list: ";
    printList(l);

    // remove function removes all occurrences of the specified element from the list
    l.remove(1);
    std::cout << "List after removing 1: ";
    printList(l);

    // remove_if function removes elements which satisfy the condition speicifed in the remove_if argument
    l.remove_if([](int x) {return x > 2;});
    std::cout << "List after removing elements greater than 2: ";
    printList(l);

    */
    // emplace, emplace_front and emplace_back is used in case where we do not want a copy of the object
    // which is passed as an argument to be created in order to boost the performance slightly
    
    // the main difference between insert and emplace is that: 
    // for insert we need to pass an already constructed object for it to be inserted to the container
    // for emplace, we can pass the arguments for the constructor to it for it to construct an object and insert it
    // in both cases, the type of constructor run is different (copy and parameterised respectively)

    std::list<A> container;

    std::cout << "construct 2 times A:\n";
    A two { "two" };
    A three { "three" };
    
    std::cout << "insert:\n";
    A zero("zero");
    container.insert(container.begin(), zero);

    std::cout << "emplace:\n";
    container.emplace(container.end(), "one"); 
    
    return 0;
}