// set STL in CPP
#include <iostream>
#include <set>

/*
    IMPORTANT LINKS:
    https://chat.openai.com/c/a8eca3ca-af79-4a0d-b3e9-01a27ea72bcb (SET AND RED-BLACK TREES EXPLANATION)
    https://stackoverflow.com/questions/1349734/why-would-anyone-use-set-instead-of-unordered-set (NEED FOR SET AND UNORERED_SET AS PER REQUIREMENTS)
    https://stackoverflow.com/questions/4343130/why-does-stl-set-have-count-when-all-elements-are-supposed-to-be-unique (WHY DOES STD::SET HAVE COUNT METHOD)
*/

// associative containers are those which implement sorted data structures which facilitate logarithmic time searching
// this helps in applications where fast lookup and manipulation times are needed

// set is an associative container which is meant to store unique keys and in sorted order. sorting is done using the comparator given
// it is internally implemented as a red-black tree - which is a self-balancing binary search tree which maintains balance during
// insertion and deletion operations, thus guaranteeing efficient searching, insertion and deletion operations. 
// supports bidirectional iteration, expands and contracts dynamically

// iterators - used to print the set
void printSet(std::set<int> s) {
    for(auto it = s.begin(); it != s.end(); it++) {
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
    std::set<int> s{1,2,3,4,5};

    // bidirectional traversal allowed - normal and reverse iterators
    std::cout << "Set contents: ";
    printSet(s);

    // printing in reverse order using reverse iterators
    std::cout << "Set contents in reverse order: ";
    for(auto it = s.rbegin(); it != s.rend(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // insert - allows to insert keys into the set. if duplicates are inserted, ignored
    // time complexity is logarithmic in the size of the container
    // a pair is returned - an iterator pointing to the element inserted or the element that prevented the insertion, and a boolean
    // value that is true when insertiom is successful and false otherwise.
    auto iter1 = s.insert(1);
    auto iter2 = s.insert(9);
    std::cout << *iter1.first << " " << (iter1.second ? "insertion successful" : "insertion failed") << std::endl;
    std::cout << *iter2.first << " " << (iter2.second ? "insertion successful" : "insertion failed") << std::endl;
    std::cout << "After inserting elements: ";
    printSet(s);

    // we can also insert a range of elements from a valid container - again if duplicates are present the insertion does not happen
    // takes N.log(size + N) time, where N is the number of elements inserted
    int arr[] = {4,5,6,7,8};
    s.insert(arr, arr + std::size(arr));
    std::cout << "After inserting elements from container: ";
    printSet(s);

    // functions to check the capacity of the set
    std::cout << "Size of the set: " << s.size() << std::endl;
    std::cout << "Maximum size of the set: " << s.max_size() << std::endl; 

    // extract - used to get the key from the set - takes logarithmic time since it is nothing but searching in BST
    // note that the extracted element will no longer stay a part of the set
    auto node1 = s.extract(5);
    std::cout << (node1.empty() ? "Extraction failed!" : "Successfully extracted!") << std::endl; 
    std::cout << "Extracted value: " << node1.value() << std::endl;
    
    // if node not found, empty node returned, if we try to dereference it we get segmentation fault
    auto node2 = s.extract(-3);
    std::cout << (node2.empty() ? "Extraction failed!" : "Successfully extracted!") << std::endl; 

    // erase - used to remove elements from the set
    // erasing one element, the return value is the iterator following the removed element
    auto it = s.erase(s.begin());
    std::cout << "First element removed, new first element: " << *it << std::endl;

    // when key is specified for erasing, the number of elements deleted (0 or 1) is returned
    auto num1 = s.erase(4);     // element in set
    std::cout << "Number of erased elements: " << num1 << std::endl;
    auto num2 = s.erase(-1);    // element not in set
    std::cout << "Number of erased elements: " << num2 << std::endl;

    std::cout << "Set after operations: ";
    printSet(s);

    // count - returns the number of elements that match the specified key
    // time complexity is logarithmic in the size of the container, linear in the number of elements found
    std::cout << "Count method:\n";
    std::cout << "Is 5 present in the set?: " << (s.count(5) > 0 ? "Yes" : "No") << std::endl;
    std::cout << "Is 7 present in the set?: " << (s.count(7) > 0 ? "Yes" : "No") << std::endl;

    // find - used to find an element of the specified value. an iterator is returned if found, otherwise after end is returned.
    // time complexity is logarithmic in the size of the container
    std::cout << "Find method:\n";
    it = s.find(7);
    std::cout << "Is 6 present in the set?: " << (it == s.end() ? "No" : "Yes") << std::endl;
    it = s.find(1);
    std::cout << "Is 1 present in the set?: " << (it == s.end() ? "No" : "Yes") << std::endl;

    // both find and count have the same time complexity, the usage depends on the choice
    // if we need an iterator pointing to the found element, use find
    // if we only need to check the presence of element, use count

    // contains - used to check the presence of an element in the set
    // returns a boolean value - true if found, false otherwise.
    std::cout << "Contains method:\n";
    std::cout << "Is 9 present in the set?: " << (s.contains(9) ? "Yes" : "No") << std::endl;

    std::cout << "Set elements: ";
    printSet(s);
    // lower_bound - returns an iterator pointing to the first element >= given value, if no such value found returns past-the-end iterator
    // upper_bound - returns an iterator pointing to the first element > given value, if no such value found returns past-the-end iterator
    auto lower = s.lower_bound(6);
    auto upper = s.upper_bound(6);
    std::cout << "Lower bound value for 6 in set: " << *lower << std::endl;
    std::cout << "Upper bound value for 6 in set: " << *upper << std::endl;

    // equal_range - returns a pair of iterators which specifies the range of elements which are equal to the given key
    // these iterators are usually the lower bound and the upper bound for the given key
    auto range = s.equal_range(7);
    std::cout << "The range of elements is: " << *(range.first) << " to " << *(range.second) << std::endl;

    // clear - clears the content of the set
    s.clear();
    std::cout << "After clear: ";
    printSet(s);

    // merge - used to merge one set into another - duplicates are omitted and remain in the source set
    // time complexity - N * log(size() + N)), where N is the source size
    std::set<int> s1{1,2,3,4,5};
    std::set<int> s2{4,5,6,7,8,9};
    std::cout << "Original sets:\n";
    std::cout << "S1: "; printSet(s1);
    std::cout << "S2: "; printSet(s2);
    s1.merge(s2);
    std::cout << "After merging:\n";
    std::cout << "S1: "; printSet(s1);
    std::cout << "S2: "; printSet(s2);
    */

    // emplace and emplace_hint are applied for achieving faster performance for insertion when the container involves complex objects
    std::set<A> s;

    std::cout << "construct object of A twice:\n";
    A one{1};
    A two(2);

    std::cout << "insert:\n";
    A three(3);
    s.insert(three);

    std::cout << "emplace:\n";
    s.emplace(4);

    std::cout << "emplace with hint:\n";
    s.emplace_hint(s.begin(), 0);
    std::cout << " first element: " << s.begin()->x << std::endl;

    return 0;
}