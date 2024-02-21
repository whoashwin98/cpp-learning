// unordered_map STL in CPP
#include <iostream>
#include <vector>
#include <unordered_map>

// unordered_map is an associative container that consists of key-value pairs with unique keys
// searching, insertion and deletion takes average constant time complexity
// the elements are not sorted in any particular order, rather they are organised into buckets - the bucket which is assigned to an element depends on its hash
// if hash values are same for two different keys, they appear in the same bucket, allowing faster access (chaining for handling collisions)
// automatic resizing is done by this container in order to maintain a load factor closest to 1 as possible (efficient performance)
// we can provide a custom hashing function or use the defaults provided by the compiler

// iterators are only invalidated when rehash, reserve, and clear operations are performed
// the same goes for any other function which leads to these functions being called

// using iterators to print the map contents
void printUnorderedMap(std::unordered_map<std::string, int>& mp) {
    for(auto it = mp.begin(); it != mp.end(); it++) {
        std::cout << "(" << it->first << ", " << it->second << ")" << std::endl;
    }
    std::cout << std::endl;
}

std::string printKeyValue(std::string key, int value) {
    return "(" + key + ", " + std::to_string(value) + ")";
}

// custom hash function
struct hash {
    constexpr std::size_t operator()(const std::string& x) const noexcept {
        return x.size();
    }
};

// custom hash and key-equal functions for unordered_map
class StringHash {
    public:
    std::size_t operator()(const std::string& str) const {
        return str.length();
    }
};

class StringKeyEqual {
    public:
    bool operator()(const std::string& lhs, const std::string& rhs) const {
        return lhs.length() < rhs.length();
    }
};


int main() {
    /*
    std::unordered_map<std::string, int> mp;

    // insert - used to insert elements (as key-value pairs) into the map. note that duplication of keys is not allowed
    // note that for insertion using the [] operator, the key must be copy constructible, and the value must be default constructible
    // time complexity of insertion is average case constant
    mp["two"] = 4;
    mp["nine"] = 9;
    std::cout << "After inserting with []: " << std::endl;
    printUnorderedMap(mp); 
    
    mp["two"] = 2;
    std::cout << "After updating with []: " << std::endl;
    printUnorderedMap(mp); 

    // insert with pair - returns a pair: an iterator and a boolean value
    // iterator points to the element inserted, or the element that prevented the insertion, boolean gives true if the insertion is successful and false otherwise
    // time complexity is constant on average
    auto it1 = mp.insert(std::pair{"one", 1});
    std::cout << (it1.second ? "Insertion successful!" : "Insertion failed!") << std::endl; 
    it1.second && (std::cout << "Element inserted: (" << (it1.first)->first << ", " << (it1.first)->second << ")" << std::endl);

    auto it2 = mp.insert(std::pair{"nine", 13});
    std::cout << (it2.second ? "Insertion successful!" : "Insertion failed!") << std::endl; 
    it2.second && (std::cout << "Element inserted: (" << (it2.first)->first << ", " << (it2.first)->second << ")" << std::endl);

    std::cout << "After inserting pairs: " << std::endl;
    printUnorderedMap(mp);

    // insert with hint and pair - returns an iterator to the element inserted, or the element that prevented the insertion
    // inserts value in the position as close as possible, just prior to the specified position
    auto iter = mp.insert(it1.first, std::pair{"zero", 0});
    std::cout << "Element inserted: (" << iter->first << ", " << iter->second << ")" << std::endl;
    std::cout << "After inserting with hints: " << std::endl;
    printUnorderedMap(mp);

    // insert from another valid container - returns nothing
    // time complexity is average N, worst case N + N.size, where N is the number of elements inserted
    std::vector<std::pair<std::string, int>> vec{{"three", 333}, {"five", 5}, {"eight", 8}, {"ten", 10}};
    mp.insert(vec.begin(), vec.end());
    std::cout << "After inserting from vector: " << std::endl;
    printUnorderedMap(mp);

    // insert_or_assign - takes key and value as arguments. if the key already exists, the value is reassigned to the one passed as argument.
    // otherwise, it performs an insertion operation for the entire key-value pair
    // time complexity is average constant, worst case linear in container size
    it1 = mp.insert_or_assign("three", 3);
    std::cout << (it1.second ? "Insertion took place" : "Reassignment took place") << std::endl;
    std::cout << "Element inserted: (" << (it1.first)->first << ", " << (it1.first)->second << ")" << std::endl;
    it2 = mp.insert_or_assign("four", 4);
    std::cout << (it2.second ? "Insertion took place" : "Reassignment took place") << std::endl;
    std::cout << "Element inserted: (" << (it2.first)->first << ", " << (it2.first)->second << ")" << std::endl;
    std::cout << "After insert_or_assign: " << std::endl;
    printUnorderedMap(mp);

    // accessing elements - similar to maps, they only allow key-based access and not random access
    // access using the [] operator - no bounds checking, undefined behaviour if any non-existent element is tried to be accessed
    std::cout << "Accessing elements using []: " << std::endl;
    std::cout << "Value for key = 'five': " << mp["five"] << std::endl;
    std::cout << "Value for key = 'twelve': " << mp["twelve"] << std::endl;
    
    // accessing using at() - bound checking done, and an out_of_range exception is thrown when invalid access is tried
    std::cout << "Accessing elements using at(): " << std::endl;
    std::cout << "Value for key = 'three': " << mp.at("three") << std::endl;
    // std::cout << "Value for key = 'eleven': " << mp.at("eleven") << std::endl;

    // extract - used to retrieve a key-value pair using either an iterator or a given key.
    // if the value is found successfully, it is unlinked from the map and returned. otherwise, the function returns an empty node.
    // time complexity for this operation is average case constant and worst case linear in container size
    auto node1 = mp.extract(it1.first);
    std::cout << (node1.empty() ? "Extraction failed" : "Extraction successful") << std::endl;
    std::cout << "Key-value pair of extracted node: " << "(" << node1.key() << ", " << node1.mapped() << ")" << std::endl;
    auto node2 = mp.extract("thirteen");
    std::cout << (node2.empty() ? "Extraction failed" : "Extraction successful") << std::endl;
    std::cout << "After extract: " << std::endl;
    printUnorderedMap(mp);

    // functions to look at the capacity and size of the map
    std::cout << "Size of the map: " << mp.size() << std::endl;
    std::cout << "Maximum possible size of the map: " << mp.max_size() << std::endl;
    
    // count - used to find the number of elements in the map whose key matches with the given key
    // returns 1 if the element is present (only unique keys possible), and 0 if the element is not found
    // time complexity is average case constant, worst case linear in container size
    printUnorderedMap(mp);
    std::cout << "Count function: " << std::endl;
    std::cout << "Is 'four' present in the map?: " << (mp.count("four") ? "Yes" : "No") << std::endl;
    std::cout << "Is 'three' present in the map?: " << (mp.count("three") ? "Yes" : "No") << std::endl;

    // find - used to locate a particular key-value pair in the map based on the provided key
    // returns an iterator pointing to the located element if found, otherwise points to after-end of the map
    // time complexity is average case constant, worst case linear in container size
    std::cout << "Find function: " << std::endl;
    std::cout << "Key = 'eight', value = " << (mp.find("eight") == mp.end() ? "Not found" : std::to_string(mp.find("eight")->second)) << std::endl;
    std::cout << "Key = 'six', value = " << (mp.find("six") == mp.end() ? "Not found" : std::to_string(mp.find("six")->second)) << std::endl;

    // contains - used to check whether a value exists in the map for the given key
    // returns a boolean value - true if the element exists in the map, and false if the element does not exist
    std::cout << "Contains function: " << std::endl;
    std::cout << "Is 'seven' present in the map?: " << (mp.contains("seven") ? "Yes" : "No") << std::endl;
    std::cout << "Is 'two' present in the map?: " << (mp.contains("two") ? "Yes" : "No") << std::endl;

    std::cout << "After searching operations: " << std::endl;
    printUnorderedMap(mp);

    // equal_range - returns a pair of iterators, which contains the elements whose key matches with the specified key
    auto range = mp.equal_range("five");
    std::cout << "Equal range for the key 'five' is from: " << printKeyValue(range.first->first, range.first->second) << " to " <<  printKeyValue(range.second->first, range.second->second)  << std::endl;

    std::cout << std::endl << "Map before delete operations: " << std::endl;
    printUnorderedMap(mp);

    // erase - used to remove an element or a range of elements from the map
    // erase using iterator - removes the key-value pair pointed by the iterator, returns the iterator of element following the deleted element
    // time complexity is amortized constant
    // note that segmentation fault occurs if we pass an invalid iterator 
    iter = mp.erase(mp.find("twelve"));
    std::cout << "Element deleted. Next of deleted is: " << printKeyValue(iter->first, iter->second) << std::endl;

    // erase using key - removes the key-value pair whose key matches with the given key, returns the number of elements deleted
    // time complexity is average case number of elements deleted, worst case size of container
    // if a non-existent key is given, returns 0 (since no element exists, so none deleted)
    std::cout << "Number of occurrences of key 'nine' deleted are: " << mp.erase("nine") << std::endl;
    std::cout << "Number of occurrences of key 'twenty' deleted are: " << mp.erase("twenty") << std::endl;

    // erase a range of elements - removes all the key-value pairs which lie in the range first to last (last not included)
    // time complexity is average case: distance between first and last, worst case linear in container size
    // note that segmentation fault is thrown if an invalid range is given
    auto first = mp.find("five");
    auto last = mp.find("ten");
    mp.erase(first, last);
    std::cout << "After erasing a range of elements: " << std::endl;
    printUnorderedMap(mp);

    // emplace, emplace_hint and try_emplace are particularly useful when insertions are to be performed with the map types being objects
    // these funcitons save the extra process of copy constructing of objects which happens during regular insertion, by taking the object constructor
    // as its arguments and then performing the construction of object itself rather than having the user perform it.
    mp.emplace(std::make_pair("one", 1));
    mp.emplace_hint(mp.find("three"), std::make_pair("seven", 7));
    std::cout << "After emplace and emplace_hint: " << std::endl;
    printUnorderedMap(mp);

    // try_emplace - tries to emplace a key-value pair into the map. if the key does not exist, the key-value pair is emplaced into the map
    // if the specified key already exists, the operation is ignored
    // returns a pair consisting of an iterator pointing to the key-value pair (new or existing) and a boolean (true when inserted otherwise false)
    auto p1 = mp.try_emplace("twelve", 12);
    std::cout << printKeyValue(p1.first->first, p1.first->second) << ": " << (p1.second ? "Inserted" : "Ignored") << std::endl;
    auto p2 = mp.try_emplace("two", 123);
    std::cout << printKeyValue(p2.first->first, p2.first->second) << ": " << (p2.second ? "Inserted" : "Ignored") << std::endl;
    std::cout << "After try_emplace: " << std::endl;
    printUnorderedMap(mp);

    // BUCKET INTERFACE FUNCTIONS

    // there are iterators for each bucket which helps access and iterate them separately
    std::cout << "Number of buckets: " << mp.bucket_count() << std::endl;
    std::cout << "Maximum number of buckets: " << mp.max_bucket_count() << std::endl;

    // printing all buckets, along with their size, using the bucket iterators
    for(int i=0; i<mp.bucket_count(); i++) {
        auto start = mp.begin(i);
        auto end = mp.end(i);
        std::cout << "Bucket " << i << " Size: " << mp.bucket_size(i) << "\tContents: ";
        for(auto it = start; it != end; it++) {
            std::cout << "(" << it->first << ", " << it->second << "), ";
        }
        std::cout << std::endl;
    }

    // finding which bucket an element belongs to using the bucket() function
    std::cout << "The pair (\"seven\", 7) is assigned to the bucket: " << mp.bucket("seven") << std::endl;
    // this key does not exist, but its bucket is calculated without any errors
    std::cout << "The pair (\"nineteen\", 19) is assigned to the bucket: " << mp.bucket("nineteen") << std::endl;
    printUnorderedMap(mp);

    // HASH POLICY FUNCTIONS    
    // load_factor - returns the average number of elements per bucket
    std::cout << "Load factor of the map is: " << mp.load_factor() << std::endl;
    // max_load_factor - returns the maximum average number of elements per bucket
    std::cout << "Maximum load factor of the map is: " << mp.max_load_factor() << std::endl;

    // rehash - changes the number of buckets in the unordered_set to a value which is not less than the specified value
    // it is responsible for resizing and reorganizing the hash table when number of elements exceeds a threshold
    // main purpose of rehashing is to ensure that it remains efficient in terms of performance by keeping the load factor within an acceptable range
    // smaller load leads to fewer collisions and hence better performance

    // reserve - sets the number of buckets to a value which is not less than the specified value, then rehashes thhe container
    // it guarantees that there will be no rehashing if number of elements inserted into the hashmap are not more than the reserved number

    // time complexity of both rehash and reserve is average linear in the size of the set, worst case quadratic
    mp.clear();
    mp.reserve(3); // reserves at least 6 buckets
    std::cout << "Initial bucket count: " << mp.bucket_count() << std::endl;
    std::vector<std::pair<std::string, int>> v{{"three", 333}, {"five", 5}, {"eight", 8}, {"ten", 10}, {"seven", 7}};
    mp.insert(v.begin(), v.end());
    std::cout << "Bucket count after insertions: " << mp.bucket_count() << std::endl;
    // rehash to have more number of buckets
    mp.rehash(12);
    std::cout << "Bucket count after rehash: " << mp.bucket_count() << std::endl;

    // clear - clears all key-value pairs from the map
    mp.clear();
    std::cout << "After clear: " << std::endl;
    printUnorderedMap(mp);

    // unordered_map with custom hash function
    std::unordered_map<std::string, int, hash> mp;
    std::vector<std::pair<std::string, int>> v{{"three", 333}, {"five", 5}, {"eight", 8}, {"ten", 10}, {"seven", 7}};
    mp.insert(v.begin(), v.end());
    for(int i=0; i<mp.bucket_count(); i++) {
        auto start = mp.begin(i);
        auto end = mp.end(i);
        std::cout << "Bucket " << i << " Size: " << mp.bucket_size(i) << "\tContents: ";
        for(auto it = start; it != end; it++) {
            std::cout << "(" << it->first << ", " << it->second << "), ";
        }
        std::cout << std::endl;
    }
    */

    // unordered_map with custom hash and custom key-equal functor
    std::unordered_map<std::string, int, StringHash, StringKeyEqual> mp;
    mp.insert({"first", 1});
    mp.insert({"second", 2});
    mp.insert({"zero", 0});
    mp.insert({"seventh", 7});
    mp.insert({"eleventh", 11});
    mp.insert({"fourth", 4});

    // printing the map contents
    for(int i=0; i<mp.bucket_count(); i++) {
        auto begin = mp.begin(i);
        auto end = mp.end(i);
        std::cout << "Bucket " << i << " -> ";
        std::cout << "Size: " << mp.bucket_size(i) << "\tContents: ";
        for(auto it = begin; it != end; it++) {
            std::cout << "(" << it->first << ", " << it->second << ")" << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}