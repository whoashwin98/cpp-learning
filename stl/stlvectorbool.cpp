// the special boolean vector type in CPP
#include <iostream>
#include <vector>

// std::vector<bool> is a specialised template instantiation of the std::vector container, which is designed to store boolean values in a compact form

// it is typically achieved by using a single bit to represent a boolean value, rather than using an entire byte or more (depending on the implementation)
// it is defined specially in the C++ standards because it is designed to behave in a different manner than the usual std::vector<T>
// due to this design, we cannot address individual bits directly as regular references - a proxy object is returned when elements are accessed
// this proxy object overloads the assignment and indirection (*) operator to be able to perform read and write operations bit-wise into the boolean vector

// since the boolean vector has a peculiar design, it does not behave in the same way regular vectors of type T would, which may lead to unwanted results.
// alternatives to using std::vector<bool> are: std::deque<bool>, std::vector<char>, std::bitset, etc.

int main() {
    std::vector<int> intVec;
    intVec.push_back(1);
    intVec.push_back(2);
    intVec.push_back(3);

    std::cout << intVec.size() << " " << intVec.capacity() << std::endl;

    // the boolean vector initially returns 64 as its capacity because it is designed in a way to be able to hold
    // 64 boolean values as 64 bits in a compact manner. this capacity increases as more elements are added.
    std::vector<bool> boolVec;
    boolVec.insert(boolVec.begin(), 392, false);
    boolVec.push_back(true);
    boolVec.push_back(true);
    boolVec.push_back(true);

    std::cout << boolVec.size() << " " << boolVec.capacity() << std::endl;

    return 0;
}