// algorithms in CPP STL
#include <iostream>
#include <algorithm>
#include <vector>

// the STL algorithm library defines functions for a variety of purposes (for example: searching, sorting, counting, manipulating, etc.) designed to
// operate on a range of elements. there are different kinds of algorithms that perform different set of operations.

int main() {
    // vector being used for all algorithms here, we can make use of any container that fulfills the requirements of the function being invoked
    std::vector<int> vec{1,2,3,4,5,6,7,8,9,10};

    // NON-MODIFYING SEQUENCE OPERATIONS - do not modify the underlying container 

    // for_each - applies the function passed to it as an argument to the range of elements specified by the iterators
    // returns a function which is called immediately
    // time complexity is dist * complexity of f, where dist = std::distance(first, last)

    // using for-each to print the vector element-wise
    std::cout << "Original vector using for-each: ";
    auto printFunc = [](const int& n) { std::cout << n << " "; };
    std::for_each(vec.begin(), vec.end(), printFunc);
    std::cout << std::endl;

    // using for-each to manipulate a select range of elements in the vector
    // this is in-place modification of elements 
    std::for_each(vec.begin() + 3, vec.end() - 3, [](int& n) { n = n + 100; });
    std::cout << "After operation: ";
    for(auto ele : vec) {
        std::cout << ele << " ";
    }
    std::cout << std::endl;

    // for_each_n - applies the function passed to it as an argument to the range of elements specified by a starting iterator, and a numeric size
    // returns an iterator that points to the first + n
    // time complexity is n * complexity of f

    // using for-each-n to print the vector element-wise
    std::cout << "Original vector using for-each-n: ";
    std::for_each_n(vec.begin(), vec.size(), printFunc);
    std::cout << std::endl;

    // usin for-each-n to modify a select range of elements in the vector
    // again this is in-place modification of elements
    std::for_each_n(vec.begin() + 3, 4, [](int& n) { n = n * 3; });
    std::cout << "After operation: ";
    for(auto ele : vec) {
        std::cout << ele << " ";
    }
    std::cout << std::endl;

    // all_of, any_of and none_of - used to check if all, any or none of the elements in the range satisfy the condition given by the unary
    // predicate - returns true if successful, otherwise returns false
    // time complexity is (last - first) * complexity of predicate
    std::cout << "all_of, any_of and none_of functions: " << std::endl;
    bool flag = std::all_of(vec.begin(), vec.begin() + 6, [](const int& n){ return (n > 10 == 0); });
    std::cout << "All of the elements from 1 to 6 are single digit: " << (flag ? "Yes" : "No") << std::endl;
    flag = std::any_of(vec.begin() + 2, vec.begin() + 6, [](const int& n){ return n > 300; });
    std::cout << "Any of the elements from 2 to 6 are greater than 300: " << (flag ? "Yes" : "No") << std::endl;
    flag = std::none_of(vec.begin() + 3, vec.end() - 1, [](const int& n){ double x = std::sqrt(n); return std::abs(x - (int)x) == 0; });
    std::cout << "None of the elements from 3 to 9 are perfect squares: " << (flag ? "Yes" : "No") << std::endl;

    // find, find_if and find_if_not - used to find an element in the container. find simply returns an iterator to the first occurrence of the element,
    // find_if searches for an element for which the specified predicate is true, and find_if_not searches for an element for which the specified
    // predicate is false
    // time complexity is N for find, N * complexity of predicate for find_if and find_if_not (N = distance between first and last)
    std::cout << "find functions: " << std::endl;
    auto iter = std::find(vec.begin(), vec.end(), 8);
    std::cout << "Is the element 8 present in the vector?: " << (iter == vec.end() ? "No" : "Yes") << std::endl;
    iter = std::find(vec.begin(), vec.end(), 7);
    std::cout << "Is the element 7 present in the vector?: " << (iter == vec.end() ? "No" : "Yes") << std::endl;

    iter = std::find_if(vec.begin() + 2, vec.begin() + 7, [](const int& n){ return n % 13 == 0; });
    std::cout << "The number that is divisible by 13, and lies between the 2nd and 7th element is: " << *iter << std::endl;
    iter = std::find_if(vec.begin() + 3, vec.begin() + 7, [](const int& n){ double x = std::sqrt(n); return std::abs(x - (int)x) == 0; });
    std::cout << "The number that is a perfect square in the range 3rd and 7th element is: " << (iter == (vec.begin() + 7) ? "Not Found" : std::to_string(*iter)) << std::endl;

    iter = std::find_if_not(vec.begin(), vec.begin() + 5, [](const int& n){ return (n > 10 == 0); });
    std::cout << "The first non-single digit number that lies between the 1st and 5th element is: " << *iter << std::endl;

    // find_end - used to find the last occurrence of the speicified sequence in the given range of container
    // returns an iterator that points to the beginning of the last occurrence of given sequence, if not found then points to 'last'
    // time complexity is S.(N-S+1), where S = range of sequence, N = range of container
    std::vector<int> v{1,2,3,4,5,1,2,3,7,8,9,1,2,10,11};
    std::vector<int> seq{1,2,3};
    iter = std::find_end(v.begin(), v.end(), seq.begin(), seq.end());
    std::cout << "The last occurrence of the given sequence starts from the index: " << (iter == (v.end()) ? "Not Found" : std::to_string(std::distance(v.begin(), iter))) << std::endl;

    // find_first_of - used to find the first occurrence of any of the elements in the given sequence, in the main container 
    // returns an iterator that points to the first element found from the sequence, otherwise points to the 'last' of container range
    // time complexity is N.S where S = range of sequence, N = range of container
    std::vector<int> haystack = {1, 2, 3, 4, 5};
    std::vector<int> needles = {6, 7, 3};
    iter = std::find_first_of(haystack.begin(), haystack.end(), needles.begin(), needles.end());
    std::cout << "The element found is " << *iter << std::endl;
    std::cout << "Index in main container: " << std::distance(haystack.begin(), iter) << std::endl;

    // adjacent_find - searches for the first occurrence of two adjacent elements in a sequence that are equal or satisfy a specified binary predicate
    // returns an iterator to the first of the two adjacent elements found, or the end iterator if no such pair is found
    // time complexity is exactly std::min((result - first) + 1, (last - first) - 1) applications of the predicate where result is the return value.
    std::vector<int> v1 {0, 1, 2, 3, 40, 40, 41, 41, 5};
    iter = std::adjacent_find(v1.begin(), v1.end());
    std::cout << "The element found is " << *iter << " and it's next element is " << *(iter+1) << std::endl;

    

    return 0;
}