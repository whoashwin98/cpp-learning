// forward_list STL in CPP
#include <iostream>
#include <forward_list>
#include <algorithm>

/*
    IMPORTANT LINKS: 
    https://chat.openai.com/c/a0c2cd46-7ed4-4c6c-89dc-9a8307a2229f (REASON FOR SIZE FUNCTION BEING PRESENT IN LIST AND FORWARD_LIST)
*/

// forward_list - a container that supports fast insertion and removal of elements from anywhere in the container
// random access is not supported (implemented as a singly linked list)
// compared to std::list this provides more memory efficiency as we do not need to store two pointers
// supports iteration in only one direction, does not invalidate iterators on modification of the list

// size operation is not given as a design choice - to calculate the size we have to traverse the list which would take
// linear time. users are encouraged to iterate through the lists manually if they need to calculate the size

// this container has a special iterator - before_begin(), which returns an iterator that points before the first element
// it is especially used for the functions like insert_after, erase_after, etc. where we might need to delete the first element

void printList(std::forward_list<int> fl) {
    for(auto it : fl) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}

int main() {
    /*
    std::forward_list<int> fl;

    // push_front - adds an element to the front of the list
    fl.push_front(1);
    std::cout << "After push_front: ";
    printList(fl);

    // insert_after - inserts element(s) after the specified position in the list
    // note that for inserting at the end, we cannot directly use the end iterator, instead we need to iterate manually 
    // from the beginning to the end (linear time) and then perform the insertion

    fl.insert_after(fl.begin(), -1);
    std::cout << "After inserting 1 element at pos: ";
    printList(fl);

    fl.insert_after(fl.begin(), 4, 0);
    std::cout << "After inserting 4 duplicate elements at pos: ";
    printList(fl);

    int arr[] = {2,3,4,5,6,7};
    int n = sizeof(arr) / sizeof(arr[0]);
    auto iter = fl.begin();
    iter++;
    fl.insert_after(iter, arr, arr+n);
    std::cout << "After inserting elements from array: ";
    printList(fl);

    // functions to display the capacity of the list
    std::cout << "Maximum possible size of the list: " << fl.max_size() << std::endl;
    // manually calculating the size of the list
    int size = 0;
    iter = fl.begin();
    while(iter != fl.end()) { iter++; size++; }
    std::cout << "Size of the list: " << size << std::endl;

    // pop_front - removes one element from the front of the list
    fl.pop_front();
    std::cout << "After pop_front: ";
    printList(fl);

    // erase_after - remove element(s) following the given position
    // it is constant in time for deleting one element, but linear in time for deleting a range of elements
    iter = fl.begin();
    iter++; iter++;
    fl.erase_after(iter);
    std::cout << "After erasing 1 element from pos: ";
    printList(fl);

    auto i1 = fl.begin(), i2 = fl.begin();
    i1++;
    int i=0;
    while(i < 5) { i++; i2++; }
    fl.erase_after(i1, i2);  // note that the last element is excluded from the range
    std::cout << "After erasing a range of elements: ";
    printList(fl);

    // resize - reduce or increase the size of the list as per the argument provided
    // if new size is less than the current size, other elements are discarded
    // if new size is more than the current size, the new empty elements are filled with a placeholder value (default 0)
    fl.resize(2);
    std::cout << "After reducing the size: ";
    printList(fl);
    fl.resize(10, -2);
    std::cout << "After expanding the size: ";
    printList(fl);

    // clear - removes all elements from the list
    fl.clear();
    std::cout << "After clear: ";
    printList(fl);

    // operations on forward_list - merge, splice_after, reverse, unique, sort, etc.
    std::forward_list<int> l1{4,2,1,3};
    std::forward_list<int> l2{6,4,5,5,5,5,4,4,6,8,9,9,7};

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
    l2.unique();
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

    // splice_after - moves elements from a list after a given position to another list
    // we can move all elements or a range of elements between lists
    l2.splice_after(l2.before_begin(), l1);
    std::cout << "Lists after splice_after: " << std::endl;
    printList(l1);
    printList(l2);

    auto it1 = l2.begin(), it2 = l2.begin();
    std::advance(it1, 3);
    std::advance(it2, 7);   // last element not included in the range of elements spliced
    l1.splice_after(l1.before_begin(), l2, it1, it2);
    std::cout << "Lists after splice_after 2: " << std::endl;
    printList(l1);
    printList(l2);
    
        // remove and remove_if - used to remove elements from the list based on conditions
    // makes exactly N comparisons (N = size of list) hence linear time to run
    // do not invalidate iterators since they modify the internal pointers to skip over the elements being removed
    std::forward_list<int> l{1, 100, 2, 3, -1, 5, 4, 1, 1, 1, 4, 3};
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

    // note that emplace_front and emplace_after works the same way as it does in other STL containers
    
    */

    return 0;
}