// map STL in CPP
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>

/*
    IMPORTANT LINKS:
    https://chat.openai.com/c/64fd048c-3193-441e-9429-91676165258c (STD::MAP AND ITS USE CASES)

*/

// maps are associative containers that contain key-value pairs, but the keys are unique (note that corresponding values can be updated)
// this container is implemented using red-black trees - a sorted order is maintained, and it provides logarithmic insertion, deletion and search times
// supports sorted order iteration, expands and contracts dynamically
// it does not support random access using indices, but it supports key-based access
// note that the mapped type must be default-constructible since sorted order is to be maintained

// using iterators to print map contents
void printMap(std::map<std::string, int>& mp) {
    for(auto it = mp.begin(); it != mp.end(); it++) {
        std::cout << it->first << " -> " << it->second << std::endl;
    }
    std::cout << std::endl;
}

std::string printKeyValue(std::string key, int value) {
    return "(" + key + ", " + std::to_string(value) + ")";
}

int main() {

    std::map<std::string, int> mp;

    // insert - used to insert elements (as key-value pairs) into the map. note that duplication of keys is not allowed
    // inserting elements using the [] operator - note that the key must be copy constructible, and the value must be both default and copy constructible
    // time complexity is logarithmic in the size of the container
    mp["two"] = 4;
    mp["eleven"] = 11;
    std::cout << "After insertion with []: " << std::endl;
    printMap(mp);
    
    mp["two"] = 2;  // key already exists - value is updated
    std::cout << "After updating with []: " << std::endl;
    printMap(mp);

    // insert with pair - returns a pair: an iterator and a boolean value
    // iterator points to the element inserted, or the element that prevented the insertion, boolean gives true if the insertion is successful and false otherwise
    // time complexity is logarithmic in the size of the container
    auto it1 = mp.insert(std::pair{"one", 1});
    std::cout << (it1.second ? "Insertion successful" : "Insertion failed") << std::endl; 
    std::cout << "Element inserted: " << (it1.first)->first << " -> " << (it1.first)->second << std::endl;

    auto it2 = mp.insert(std::pair{"eleven", 13});
    std::cout << (it2.second ? "Insertion successful" : "Insertion failed") << std::endl; 
    std::cout << "Element inserted: " << (it2.first)->first << " -> " << (it2.first)->second << std::endl;

    std::cout << "After inserting pairs: " << std::endl;
    printMap(mp);

    // insert with hint and pair - returns an iterator to the element inserted, or the element that prevented the insertion
    // inserts value in the position as close as possible, just prior to the specified position
    auto iter = mp.insert(it2.first, std::pair{"zero", 0});
    std::cout << "Element inserted: " << iter->first << " -> " << iter->second << std::endl;
    std::cout << "After inserting with hints: " << std::endl;
    printMap(mp);

    // insert from another valid container - returns nothing
    // time complexity is N.log(N + size), where N is the number of elements inserted
    std::vector<std::pair<std::string, int>> vec{{"three", 3}, {"five", 5}, {"eight", 88}, {"ten", 10}};
    mp.insert(vec.begin(), vec.end());
    std::cout << "After inserting from vector: " << std::endl;
    printMap(mp);

    // insert_or_assign - takes key and value as arguments. if the key already exists in the map, reassigns its value to the new value
    // otherwise, it performs insertion, creating a new key-value pair
    // time complexity is logarithmic in the size of the container
    it1 = mp.insert_or_assign("eight", 8);
    std::cout << (it1.second ? "Insertion took place" : "Reassignment took place") << std::endl;
    std::cout << "Key-value pair is: " << it1.first->first << " -> " << it1.first->second << std::endl;
    it2 = mp.insert_or_assign("nine", 9);
    std::cout << (it2.second ? "Insertion took place" : "Reassignment took place") << std::endl;
    std::cout << "Key-value pair is: " << it2.first->first << " -> " << it2.first->second << std::endl;
    std::cout << "After insert_or_assign: " << std::endl;
    printMap(mp);

    // accessing elements - since maps are associative data structures, they allow key-based access.
    // access using the [] operator - no bounds checking, undefined behaviour if any non-existent element is tried to be accessed
    std::cout << "Accessing elements using []: " << std::endl;
    std::cout << "Value for key = 'ten': " << mp["ten"] << std::endl;
    std::cout << "Value for key = 'thirteen': " << mp["thirteen"] << std::endl;     // here default integer value is assigned to "thirteen"
    
    // access using the at() method - bound checking done, and an out_of_range error thrown if invalid access is tried
    std::cout << "Accessing elements using at(): " << std::endl;
    std::cout << "Value for key = 'five': " << mp.at("five") << std::endl;
    // std::cout << "Value for key = 'four': " << mp.at("four") << std::endl;  // causes exception - out_of_range and program stops here

    // extract - used to retrieve a key-value pair using either an iterator or a given key.
    // if the value is found successfully, it is unlinked from the map and returned. otherwise, the function returns an empty node.
    // time complexity for this operation is amortized constant (iterator) and logarithmic (key)
    auto node1 = mp.extract(it1.first);
    std::cout << (node1.empty() ? "Extraction failed" : "Extraction successful") << std::endl;
    std::cout << "Key-value pair of extracted node: " << node1.key() << " -> " << node1.mapped() << std::endl;
    auto node2 = mp.extract("twelve");
    std::cout << (node2.empty() ? "Extraction failed" : "Extraction successful") << std::endl;
    std::cout << "After extract: " << std::endl;
    printMap(mp);

    // functions to look at the capacity and size of the map
    std::cout << "Size of the map: " << mp.size() << std::endl;
    std::cout << "Maximum possible size of the map: " << mp.max_size() << std::endl;
    

    // count - used to find the number of elements in the map whose key matches with the given key
    // returns 1 if the element is present (only unique keys possible), and 0 if the element is not found
    // time is logarithmic in the size of the container, plus linear in the number of elements found
    printMap(mp);
    std::cout << "Count function: " << std::endl;
    std::cout << "Is 'three' present in the map?: " << (mp.count("three") ? "Yes" : "No") << std::endl;  
    std::cout << "Is 'six' present in the map?: " << (mp.count("six") ? "Yes" : "No") << std::endl;  

    // find - used to locate a particular key-value pair in the map based on the provided key
    // returns an iterator pointing to the located element if found, otherwise points to after-end of the map
    // time is logarithmic in the size of the container
    std::cout << "Find function: " << std::endl;
    std::cout << "Key = 'one', value = " << (mp.find("one") == mp.end() ? "Not found" : std::to_string(mp.find("one")->second)) << std::endl;
    std::cout << "Key = 'twelve', value = " << (mp.find("twelve") == mp.end() ? "Not found" : std::to_string(mp.find("twelve")->second)) << std::endl;

    // contains - used to check whether a value exists in the map for the given key
    // returns a boolean value - true if the element exists in the map, and false if the element does not exist
    std::cout << "Contains function: " << std::endl;
    std::cout << "Is 'four' present in the map?: " << (mp.contains("four") ? "Yes" : "No") << std::endl;
    std::cout << "Is 'two' present in the map?: " << (mp.contains("two") ? "Yes" : "No") << std::endl;

    std::cout << "After searching operations: " << std::endl;
    printMap(mp);

    // lower_bound - returns an iterator to the first element that is greater than or equal to the specified key
    // upper_bound - returns an iterator to the first element that is strictly greater than the specified key
    auto lower = mp.lower_bound("three");
    auto upper = mp.upper_bound("three");
    std::cout << "Lower bound value for the key 'three': " << lower->second << std::endl;
    std::cout << "Upper bound value for the key 'three': " << upper->second << std::endl;

    // equal_range - returns a pair of iterators, which contains the elements whose key matches with the specified key
    auto range = mp.equal_range("five");
    std::cout << "Equal range for the key 'five' is from: " << printKeyValue(range.first->first, range.first->second) << " to " <<  printKeyValue(range.second->first, range.second->second)  << std::endl;

    std::cout << std::endl << "Map before delete operations: " << std::endl;
    printMap(mp);

    // erase - used to remove an element or a range of elements from the map
    // erase using iterator - removes the key-value pair pointed by the iterator, returns the iterator of element following the deleted element
    // time complexity is amortized constant
    // note that segmentation fault occurs if we pass an invalid iterator 
    iter = mp.erase(mp.find("thirteen"));
    std::cout << "Element deleted. Next of deleted is: " << printKeyValue(iter->first, iter->second) << std::endl;

    // erase using key - removes the key-value pair whose key matches with the given key, returns the number of elements deleted
    // time complexity is logarithmic in the size of the container, plus the number of occurrences deleted
    // if a non-existent key is given, returns 0 (since no element exists, so none deleted)
    std::cout << "Number of occurrences of key 'zero' deleted are: " << mp.erase("zero") << std::endl;
    std::cout << "Number of occurrences of key 'twenty' deleted are: " << mp.erase("twenty") << std::endl;

    // erase a range of elements - removes all the key-value pairs which lie in the range first to last (last not included)
    // time complexity is logarithic in the size of the container, plus linear in distance between first and last
    // note that segmentation fault is thrown if an invalid range is given
    auto first = mp.find("five");
    auto last = mp.find("ten");
    mp.erase(first, last);
    std::cout << "After erasing a range of elements: " << std::endl;
    printMap(mp);

    // emplace, emplace_hint and try_emplace are particularly useful when insertions are to be performed with the map types being objects
    // these funcitons save the extra process of copy constructing of objects which happens during regular insertion, by taking the object constructor
    // as its arguments and then performing the construction of object itself rather than having the user perform it.
    mp.emplace(std::make_pair("one", 1));
    mp.emplace_hint(mp.find("three"), std::make_pair("seven", 7));
    std::cout << "After emplace and emplace_hint: " << std::endl;
    printMap(mp);

    // try_emplace - tries to emplace a key-value pair into the map. if the key does not exist, the key-value pair is emplaced into the map
    // if the specified key already exists, the operation is ignored
    // returns a pair consisting of an iterator pointing to the key-value pair (new or existing) and a boolean (true when inserted otherwise false)
    auto p1 = mp.try_emplace("twelve", 12);
    std::cout << printKeyValue(p1.first->first, p1.first->second) << ": " << (p1.second ? "Inserted" : "Ignored") << std::endl;
    auto p2 = mp.try_emplace("three", 123);
    std::cout << printKeyValue(p2.first->first, p2.first->second) << ": " << (p2.second ? "Inserted" : "Ignored") << std::endl;
    std::cout << "After try_emplace: " << std::endl;
    printMap(mp);

    // clear - clears all key-value pairs from the map
    mp.clear();
    std::cout << "After clear: " << std::endl;
    printMap(mp);

    return 0;

}