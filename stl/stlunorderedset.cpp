// unordered_set STL in CPP
#include <iostream>
#include <unordered_set>
#include <vector>

/*
    IMPORTANT LINKS:
    https://chat.openai.com/c/c64a119a-403b-4714-b8fa-30240ee1cf37 (UNORDERED_SET POINTS)
    https://stackoverflow.com/questions/14851249/whats-the-difference-between-the-rehash-and-reserve-methods-of-the-c-unor (REHASH VS. RESERVE)
    https://stackoverflow.com/questions/1349734/why-would-anyone-use-set-instead-of-unordered-set (NEED FOR SET AND UNORERED_SET AS PER REQUIREMENTS)
*/

// unordered_set is an associative container that contains a set of unique keys. searching, insertion and removal occur in average constant time
// there is no specific ordering maintained for elements - thus there is no overhead of sorting in this container
// internally implemented as a hash table - hence the elements are not sorted in any particular order, rather they are organized into buckets
// each element gets a bucket based on its hash value - allows fast access since once a hash is computed, it refers to the exact bucket that the element belongs to
// we can provide custom hash functions as well as custom equality functions
// modification of elements is not allowed since it may lead to corruption of the container (due to hash value change)
// iteration is allowed in only one direction (no reverse iterators)

// rehash and reserve are the only functions that always cause iterator invalidation
// insert and emplace functions cause invalidation only if they cause a rehash

// iterators used to print the set contents
void printUnorderedSet(std::unordered_set<int> us) {
    for(auto it = us.begin(); it != us.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void printBucketWise(std::unordered_set<int> us) {
    for(int i=0; i<us.bucket_count(); i++) {
        auto begin = us.begin(i);
        auto end = us.end(i);
        std::cout << "Bucket " << i << " -> ";
        std::cout << "Size: " << us.bucket_size(i) << "\tContents: ";
        for(auto it = begin; it != end; it++) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
}

// custom hash function for the unordered_set
struct hash {
    constexpr std::size_t operator()(const int& x) const noexcept {
        return x % 3;
    }
};

int main() {
    std::unordered_set<int> us{5,1,4,2,3};

    std::cout << "Original unordered_set: ";
    printUnorderedSet(us); 

    // insert - allows us to insert an element into the set. if we try to insert duplicates, it does not happen
    // average case time complexity is constant for this operation, worst case it is linear in the size of the set
    // when a value is inserted, a pair is returned - an iterator and a boolean
    // iterator points to the inserted element if successful otherwise points to the element that prevented the insertion
    // boolean is true if insertion happens otherwise false
    auto p1 = us.insert(7);
    auto p2 = us.insert(4);
    if(p1.second) { std::cout << "Insertion successful! Element is: " << *p1.first << std::endl; }
    else { std::cout << "Insertion failed!" << std::endl; }
    if(p2.second) { std::cout << "Insertion successful! Element is: " << *p2.first << std::endl; }
    else { std::cout << "Insertion failed!" << std::endl; }
    std::cout << "After insertion of elements: ";
    printUnorderedSet(us);

    // inserting an element with a hint (iterator) which is basically a suggestion as to where the search should start
    // returns an iterator that points to the inserted element if successful otherwise points to the element that prevented the insertion
    auto iter = us.insert(p1.first, 6);
    std::cout << "Inserted element using hint: " << *iter << std::endl;
    std::cout << "After insertion of elements using hint: ";
    printUnorderedSet(us);

    // we can also insert a range of elements from a valid container. note that duplicates will not be inserted and be dropped
    // time complexity of this operation is on average linear in size of container, worst case O(N*size + N) where size = size of set, N = size of container
    std::vector<int> vec{5,6,7,8,9,10};
    us.insert(vec.begin(), vec.end());
    std::cout << "After insertion from another container: ";
    printUnorderedSet(us);

    // erase - used to remove element(s) from the unordered_set
    // erasing an element using iterators - returns an iterator which points to the element after the deleted one
    // time complexity is average case constant, worst case linear in set size
    iter = us.find(6);
    auto nextDel = us.erase(iter);
    std::cout << "Deleted 6, next element: " << *nextDel << std::endl;
    std::cout << "After deleting one element: ";
    printUnorderedSet(us);

    // we can also erase a range of elements from the set - if iterators are used wrongly, segmentation fault occurs
    // time complexity is average case number of elements in range, worst case size of set
    auto start = us.find(1);
    auto end = us.find(7);
    us.erase(end, start); // ----- ?? 
    std::cout << "After deleting a range of elements: ";
    printUnorderedSet(us);

    // specify the key to the erase function to erase - returns a number which specifies the number of elements removed
    // time complexity is average case count of erased element, worst case size of set
    std::cout << "Number of 5s deleted: " << us.erase(5) << std::endl;
    std::cout << "Number of 6s deleted: " << us.erase(6) << std::endl;
    std::cout << "After deleting using keys: ";
    printUnorderedSet(us);

    // extract - it is used to retrieve an element from the hash-set, if no element found an empty node is returned
    // note that the element is removed from the hash-set once extract() retrieves it
    // time complexity is average case constant, worst case container size
    auto node1 = us.extract(1);
    auto node2 = us.extract(0);
    std::cout << (node1.empty() ? "Extraction failed!" : "Successfully extracted!") << std::endl; 
    std::cout << "Extracted value: " << node1.value() << std::endl;
    std::cout << (node2.empty() ? "Extraction failed!" : "Successfully extracted!") << std::endl; 

    // count - returns the number of elements that match the specified key
    // time complexity is average case constant
    std::cout << "Count method:\n";
    std::cout << "Is 9 present in the set?: " << (us.count(9) > 0 ? "Yes" : "No") << std::endl;
    std::cout << "Is 7 present in the set?: " << (us.count(7) > 0 ? "Yes" : "No") << std::endl;

    // find - used to find an element of the specified value. an iterator is returned if found, otherwise after end is returned.
    // time complexity is average case constant
    std::cout << "Find method:\n";
    auto it = us.find(10);
    std::cout << "Is 10 present in the set?: " << (it == us.end() ? "No" : "Yes") << std::endl;
    it = us.find(5);
    std::cout << "Is 5 present in the set?: " << (it == us.end() ? "No" : "Yes") << std::endl;

    // both find and count have the same time complexity, the usage depends on the choice
    // if we need an iterator pointing to the found element, use find
    // if we only need to check the presence of element, use count

    // contains - used to check the presence of an element in the set
    // returns a boolean value - true if found, false otherwise.
    std::cout << "Contains method:\n";
    std::cout << "Is 9 present in the set?: " << (us.contains(9) ? "Yes" : "No") << std::endl;

    std::cout << "Unordered set elements: ";
    printUnorderedSet(us);

    // equal_range - returns a pair of iterators which specifies the range of elements which are equal to the given key
    // these iterators are usually the lower bound and the upper bound for the given key
    auto range = us.equal_range(9);
    std::cout << "The range of elements is: " << *(range.first) << " to " << *(range.second) << std::endl;

    // BUCKET INTERFACE FUNCTIONS
    // functions to find number of buckets which are possible currently and the max. no. of buckets
    std::cout << "Number of buckets: " << us.bucket_count() << std::endl;
    std::cout << "Maximum number of buckets: " << us.max_bucket_count() << std::endl;

    // bucket iterators are used to iterate through buckets individually
    // bucket_size gives the size of the specified bucket
    // printBucketWise(us);

    // bucket - returns the bucket index to which the specified key belongs to
    std::cout << "The element 7 belongs to bucket: " << us.bucket(7) << std::endl;

    // HASH POLICY FUNCTIONS
    // load_factor - returns the average number of elements per bucket
    std::cout << "Load factor is: " << us.load_factor() << std::endl;

    // max_load_factor - returns the maximum average number of elements per bucket
    std::cout << "Maximum load factor is: " << us.max_load_factor() << std::endl;

    // rehash - changes the number of buckets in the unordered_set to a value which is not less than the specified value
    // it is responsible for resizing and reorganizing the hash table when number of elements exceeds a threshold
    // main purpose of rehashing is to ensure that it remains efficient in terms of performance by keeping the load factor within an acceptable range
    // smaller load leads to fewer collisions and hence better performance

    // reserve - sets the number of buckets to a value which is not less than the specified value, then rehashes thhe container
    // it guarantees that there will be no rehashing if number of elements inserted into the hashmap are not more than the reserved number

    // time complexity of both rehash and reserve is average linear in the size of the set, worst case quadratic
    us.clear();
    // reserves at least 5 buckets
    us.reserve(5);
    std::cout << "Initial bucket count: " << us.bucket_count() << std::endl;
    std::vector<int> v{5,1,2,3,9,8,7,4,10,6};
    us.insert(v.begin(), v.end());
    std::cout << "Bucket count after insertions: " << us.bucket_count() << std::endl;
    // rehash to have more number of buckets
    us.rehash(12);
    std::cout << "Bucket count after rehash: " << us.bucket_count() << std::endl;
    // printBucketWise(us);

    // clear - clears the entire unordered_set
    us.clear();
    std::cout << "After clear: ";
    printUnorderedSet(us);


    // unordered_set with custom hash function
    /*
    std::unordered_set<int, hash> us {5,1,2,4,3};
    std::vector<int> vec{5,6,7,8,9,10};
    us.insert(vec.begin(), vec.end());

    for(int i=0; i<us.bucket_count(); i++) {
        auto begin = us.begin(i);
        auto end = us.end(i);
        std::cout << "Bucket " << i << " -> ";
        std::cout << "Size: " << us.bucket_size(i) << "\tContents: ";
        for(auto it = begin; it != end; it++) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
    */
    
    // emplace and emplace_hint are applied for achieving faster performance for insertion when the container involves complex objects

    return 0;
}