// copy-swap idiom and the rules of five/three/zero
#include <iostream>
#include <vector>

// understanding the rules of five/three/zero along with the copy-swap idiom using the naive vector example
// (i.e. creating a vector class from scratch)

// rule of three - involves writing three member functions if your class involves management of a resource: destructor, copy constructor and copy assignment
// note that copy-swap idiom is used to implement the copy assignment operator
class NaiveVectorThree { 
    public:
    int *mPtr;
    size_t mSize;

    // constructor correctly initialises mPtr with a resource
    NaiveVectorThree() : mPtr(nullptr), mSize(0) {}

    // a function to implement to implement insertion at the end of NaiveVectorThree
    void push_back(int newVal) {
        // allocate new memory since size is changing
        int *newPtr = new int[mSize + 1];
        // copy all elements from original resource to newPtr
        std::copy(mPtr, mPtr + mSize, newPtr);
        // de-allocate the old resource, and make ptr point to newPtr
        delete[] mPtr;
        mPtr = newPtr;
        // finally insert the element and increment size
        mPtr[mSize++] = newVal;
    }

    // note that, without a destructor, we will face the problem of resource leak - when objects of this class go out of scope the destructor 
    // does not de-allocate this resource by itself. hence, we write a destructor manually, wherein we de-allocate all these resources
    ~NaiveVectorThree() {
        mSize = 0;
        delete[] mPtr;
    }

    // to avoid double-free problems, we write copy constructors - applies to memory or any resource you might be managing
    NaiveVectorThree(const NaiveVectorThree& rhs) {
        mPtr = new int[rhs.mSize];
        mSize = rhs.mSize;
        std::copy(rhs.mPtr, rhs.mPtr + mSize, mPtr);
    }

    // note that, assignment and initialisation are different, even though the operator involved is the same - initialisation involves creation of
    // a new object (copy constructor), whereas assignment involves assigning one object's values to the other (both have already been created)

    // copy assignment operator is written along with the destructor and copy constructor

    // now, the problem with writing the copy assignment function like this is, it is not robust with self-assignment
    NaiveVectorThree& operator=(const NaiveVectorThree& rhs) {
        delete mPtr;                                   // if it was a self assignment, we would have lost the data here itself
        mPtr = new int[rhs.mSize];
        mSize = rhs.mSize; 
        std::copy(rhs.mPtr, rhs.mPtr + mSize, mPtr);  // contains garbage values
        return *this;
    }
};

// rule of zero - if your class does not manage any resource directly, but merely uses standard library components, then strive to write 
// no special member functions (destructor, copy constructor and copy assignment operator defualted)

class NaiveVectorZero {
    public:

    // since this STL container already has all aspects of memory management implemented, so we don't need to manage it explicitly inside member functions
    std::vector<int> mData;

    // three necessary constructors explicitly defaulted
    NaiveVectorZero(const NaiveVectorZero& rhs) = default;
    NaiveVectorZero& operator=(const NaiveVectorZero& rhs) = default;
    ~NaiveVectorZero() = default;
};

// rule of five - this rule was introduced after move semantics came into picture after C++11. it requires a class which manages some kind of resource to
// have five handwritten special member functions: destructor, copy constructor, copy assignment, move constructor, and move assignment 

// move constructor transfers the ownership of the resource being assigned to the newly created object
// move assignment frees the left-hand resource first and then assigns the ownership of the right-hand resource to it

class NaiveVectorFive {
    public: 
        int* mPtr;
        size_t mSize;

        // swap member function to perform the copy-swap in assignment operators
        void swap(NaiveVectorFive& rhs) noexcept {
            using std::swap;
            swap(mPtr, rhs.mPtr);
            swap(mSize, rhs.mSize);
        }

        // constructor to initialise the vector
        NaiveVectorFive() : mPtr(nullptr), mSize(0) {}

        // copy constructor to copy from one vector to another - helps avoid double-free problem
        NaiveVectorFive(const NaiveVectorFive& rhs) {
            mPtr = new int[rhs.mSize];
            mSize = rhs.mSize;
            std::copy(rhs.mPtr, rhs.mPtr + mSize, mPtr);
        }

        // move constructor to transfer the ownership of a vector from one instance to another - helps avoid unnecessary copying
        NaiveVectorFive(NaiveVectorFive&& rhs) {
            // std::exchange function - replaces the old value of object with the new value, and returns the old value
            // which is being assigned to the current instance here
            mPtr = std::exchange(rhs.mPtr, nullptr);
            mSize = std::exchange(rhs.mSize, 0);
        }

        // copy assignment operator to free the left-hand resource and copy the right-hand resource to it (copy-swap idiom used)
        NaiveVectorFive& operator=(const NaiveVectorFive& rhs) {
            NaiveVectorFive copy(rhs);
            copy.swap(*this);
            return *this;
        }   

        // move assignment operator to free the left-hand resource and transfer ownership of the right-hand resource to it (copy-swap idiom used)
        NaiveVectorFive& operator=(NaiveVectorFive&& rhs) {
            NaiveVectorFive copy(rhs);
            copy.swap(*this);
            return *this;
        }
        
        // we can clearly notice that usage of copy-swap makes the code almost identical for the copy and move assignment member functions
        // one possible solution to this is - writing one assignment operator function, but the parameter is passed by value - copy left upto the caller
        // this introduces a new rule - rule of four (and a half which is the swap function to implement copy-swap)

        // destructor to de-allocate the resource and reset the size - helps avoid resource leaks
        ~NaiveVectorFive() {
            mSize = 0;
            delete[] mPtr;
        }
};

// this redundant assignment operator code leads to a new rule - the rule of four - where every class that manages some kind of resource directly should
// have four (and a half) special hand-written member functions: destructor, copy constructor, move constructor, by-value assignment operator (and the half
// stands for the custom swap function which can have both a non-member and member version)
class NaiveVectorFinal {
    public: 
        int* mPtr;
        size_t mSize;

        // swap member function to perform the copy-swap in assignment operators
        void swap(NaiveVectorFinal& rhs) noexcept {
            using std::swap;
            swap(mPtr, rhs.mPtr);
            swap(mSize, rhs.mSize);
        }

        // constructor to initialise the vector
        NaiveVectorFinal() : mPtr(nullptr), mSize(0) {}

        // copy constructor to copy from one vector to another - helps avoid double-free problem
        NaiveVectorFinal(const NaiveVectorFinal& rhs) {
            mPtr = new int[rhs.mSize];
            mSize = rhs.mSize;
            std::copy(rhs.mPtr, rhs.mPtr + mSize, mPtr);
        }

        // move constructor to transfer the ownership of a vector from one instance to another - helps avoid unnecessary copying
        NaiveVectorFinal(NaiveVectorFinal&& rhs) noexcept {
            // std::exchange function - replaces the old value of object with the new value, and returns the old value
            // which is being assigned to the current instance here
            mPtr = std::exchange(rhs.mPtr, nullptr);
            mSize = std::exchange(rhs.mSize, 0);
        }

        // a common assignment operator to free the left-hand resource and transfer the right-hand resource to it (copy-swap idiom used)
        // both copy and move assignment will work here - upto the compiler to do the copying job in the argument of the function
        NaiveVectorFinal& operator=(NaiveVectorFinal rhs) {
            NaiveVectorFinal copy(rhs);
            copy.swap(*this);
            return *this;
        }   

        // destructor to de-allocate the resource and reset the size - helps avoid resource leaks
        ~NaiveVectorFinal() {
            mSize = 0;
            delete[] mPtr;
        }
};

int main() {
    // NaiveVector v;
    // v.push_back(1);

    {
        // now, this line invokes the implicitly generated copy constructor, which simply copies each member - but both are still pointing to the same
        // location. now, this 'w' object gets destructed as soon as it goes out of this current block, and it takes the original NaiveVector 'v' with it.
        // NaiveVector w = v;

        // the problem described above exists with the assignment operator as well
        // NaiveVector w;
        // w = v;
    }

    // since the memory being pointed by 'v' has already been freed in the previous line, this leads to undefined behaviour
    // std::cout << v[0] << std::endl;

    return 0;

    // now when finally 'v' goes out of scope, its destructor is called, which leads to the double-free problem (freeing memory which is already freed previously)
}

