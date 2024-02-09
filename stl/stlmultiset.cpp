// multiset STL in CPP
#include <iostream>
#include <set>
#include <vector>

/*
    IMPORTANT LINKS:
    https://chat.openai.com/c/b3447542-da08-4540-b432-85a87058c8a6 (OVERVIEW OF MULTISET)
*/

// multiset is an associative container that stores keys in a sorted order. unlike sets, multisets are allowed to contain duplicate values of keys
// implemented internally as a red-black tree, thus search, insertion and deletion take place in logarithmic complexity
// supports bidirectional iteration

// iterators - used to print the set
void printMultiset(std::multiset<int> ms) {
    for(auto it = ms.begin(); it != ms.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

class A {
    public: 
    int x;
    A(int x) { this->x = x; std::cout << " constructed\n"; }
    A(const A& o) { x = o.x; std::cout << " copy constructed\n"; }
    bool operator<(const A& other) const {
        return x < other.x;
    }
};


int main() {
    /*
    std::multiset<int> ms{1,2,2,3,3,3,4,4,4,4,5};

    std::cout << "Multiset contents: ";
    printMultiset(ms);

    // printing in reverse order using reverse iterators
    std::cout << "Multiset contents in reverse order: ";
    for(auto it = ms.rbegin(); it != ms.rend(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // insert - allows to insert keys into the multiset. note that, multiset allows duplicates as well.
    // time complexity is logarithmic in the size of the container
    // an iterator is returned - which points to the element inserted
    auto iter1 = ms.insert(6);
    std::cout << "Element inserted: " << *iter1 << std::endl;
    std::cout << "Multiset after inserting new element: ";
    printMultiset(ms);
    auto iter2 = ms.insert(5); // duplicate inserted
    std::cout << "Element inserted: " << *iter2 << std::endl;
    std::cout << "Multiset after inserting duplicate element: ";
    printMultiset(ms);
    
    // we can also insert a range of elements from a valid container
    // takes N.log(size + N) time, where N is the number of elements inserted
    std::vector<int> vec{6,7,8,9,10};
    ms.insert(vec.begin(), vec.end());
    std::cout << "Multiset after inserting from vector: ";
    printMultiset(ms);

    // functions to check the capacity of the multiset
    std::cout << "Size of the multiset: " << ms.size() << std::endl;
    std::cout << "Maximum size of the multiset: " << ms.max_size() << std::endl;

    // extract - used to get keys from the multiset - takes constant time if iterator is provided, and logarithmic if key is provided
    // note that the element is removed from the multiset once it has been extracted
    auto node1 = ms.extract(5);
    std::cout << (node1.empty() ? "Extraction failed!" : "Successfully extracted!") << std::endl;
    std::cout << "Extracted value: " << node1.value() << std::endl;

    // if any node is not found, an empty node is returned, if we try to dereference it we get segmentation fault
    auto node2 = ms.extract(0);
    std::cout << (node2.empty() ? "Extraction failed!" : "Successfully extracted!") << std::endl;
    
    std::cout << "Multiset after extraction: ";
    printMultiset(ms);

    // erase - used to remove elements from the multiset
    // if key is specified, all the occurrences of that key are removed 
    // returns the number of elements removed - logarithmic + linear in the number of elements removed
    auto num = ms.erase(4);
    std::cout << "Number of 4s removed: " << num << std::endl;
    std::cout << "Multiset after erasing: ";
    printMultiset(ms);

    // if we want to remove a specific instance of a key, we pass the iterator to that key to the erase function
    // returns an iterator following this removed element - amortized constant
    auto delNode = ms.lower_bound(3);   // getting the first occurence of 3
    auto nextNode = ms.erase(delNode);
    std::cout << "Next of deleted element: " << *nextNode << std::endl;
    std::cout << "Multiset after erasing one element: ";
    printMultiset(ms); 

    // count - returns the number of elements that match the specified key, if not found 0 is returned
    // time complexity is log(size) + number of elements found
    std::cout << "Count method:\n";
    std::cout << "Number of 3s in multiset: " << ms.count(3) << std::endl;
    std::cout << "Number of 4s in multiset: " << ms.count(4) << std::endl;

    // find - used to find an element in the multiset whose value is equal to the specified key
    // returns an iterator pointing to the element in multiset if found, if not found then after end iterator is returned
    // if multiple occurrences of the specified key exist, any one's iterator is returned
    // time complexity is logarithmic in the size of the container
    std::cout << "Find method:\n";
    auto iter = ms.find(6);
    std::cout << "Is 6 present in the multiset?: " << (iter == ms.end() ? "No" : "Yes") << std::endl;
    std::cout << "Printing elements after this iterator till the end: ";
    for(auto it = iter; it != ms.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    iter = ms.find(-1); // if we try to dereference, segmentation fault
    std::cout << "Is -1 present in the multiset?: " << (iter == ms.end() ? "No" : "Yes") << std::endl;

    // both find and count have the same time complexity, the usage depends on the choice
    // if we need an iterator pointing to the found element, use find
    // if we only need to check the presence of element, use count

    // contains - used to check the presence of an element in the multiset
    // returns a boolean value - true if found, false otherwise.
    std::cout << "Contains method:\n";
    std::cout << "Is 9 present in the multiset?: " << (ms.contains(9) ? "Yes" : "No") << std::endl;
    
    std::cout << "Multiset elements: ";
    printMultiset(ms);
    // lower_bound - returns an iterator pointing to the first element >= given value, if no such value found returns past-the-end iterator
    // upper_bound - returns an iterator pointing to the first element > given value, if no such value found returns past-the-end iterator
    auto lower = ms.lower_bound(6);
    auto upper = ms.upper_bound(6);
    std::cout << "Lower bound value for 6 in set: " << *lower << std::endl;
    std::cout << "Upper bound value for 6 in set: " << *upper << std::endl;

    // equal_range - returns a pair of iterators which specifies the range of elements which are equal to the given key
    // these iterators are usually the lower bound and the upper bound for the given key
    auto range = ms.equal_range(6);
    std::cout << "Range of elements: ";
    for(auto it = range.first; it != range.second; it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // clear - clears the content of the multiset
    ms.clear();
    std::cout << "After clear: ";
    printMultiset(ms);

    // merge - used to merge one set into another - duplicates are also copied - source set is emptied
    // time complexity - N * log(size() + N)), where N is the source size
    std::multiset<int> ms1{1,2,2,3,4,5};
    std::multiset<int> ms2{4,5,6,7,7,7,8,9};
    std::cout << "Original multisets:\n";
    std::cout << "MS1: "; printMultiset(ms1);
    std::cout << "MS2: "; printMultiset(ms2);
    ms1.merge(ms2);
    std::cout << "After merging:\n";
    std::cout << "MS1: "; printMultiset(ms1);
    std::cout << "MS2: "; printMultiset(ms2);
    */
   
    // emplace and emplace_hint are applied for achieving faster performance for insertion when the container involves complex objects
    std::multiset<A> ms;

    std::cout << "construct object of A twice:\n";
    A one{1};
    A two(2);

    std::cout << "insert:\n";
    A three(3);
    ms.insert(three);

    std::cout << "emplace:\n";
    ms.emplace(4);

    std::cout << "emplace with hint:\n";
    ms.emplace_hint(ms.begin(), 0);
    std::cout << " first element: " << ms.begin()->x << std::endl;

    return 0;
}