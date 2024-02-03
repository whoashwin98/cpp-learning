// array STL in CPP
#include <iostream>
#include <array>

/*
    IMPORTANT LINKS FOR REFERENCE: 
    https://www.quora.com/What-is-the-difference-between-std-array-and-C-style-arrays-in-C
    https://stackoverflow.com/questions/60235741/in-c-what-is-the-point-of-stdarray-if-the-size-has-to-be-determined-at-compi
    https://stackoverflow.com/questions/1239938/accessing-an-array-out-of-bounds-gives-no-error-why
    https://www.reddit.com/r/cpp_questions/comments/9twbbb/stdarray_dynamic_size/
*/


// array is a container which has homogeneous elements and is of a fixed size
// unlike a C-style array, it doesn't decay to pointer type automatically

// here, this container combines the performance and accessibility of C-style arrays, as well as the benefits of
// an STL container such as knowing its own size, random access iterators, etc.

// it satisfies the requirements of Container, ReversibleContainer and SequenceContainer (partially)

// Container - an object used to store other objects and taking care of the memory used by the containing objects
// ReversibleContainer - a Container that has iterators which allow it to be iterated in a reverse fashion
// SequenceContainer - a Container that store objects of the same type in a linear arrangement

// reasons for no bounds checking in C style arrays are:
// 1. C style arrays are simply sequence of elements with contiguous addresses, and there is no bounds checking because it is exposing raw memory
// 2. Bounds checking can be performed for class types, but C-style arrays are not a class. 

// differences between C-style arrays and std::array:
// 1. C-style arrays do not provide any safety checks whereas std::array provides built-in safety checks (bound checks)
// 2. C-style arrays cannot be assigned or copied to other arrays entirely (have to copy element by element), whereas std::array can be easily copied
// 3. C-style arrays do not provide iterator support whereas std::array provides iterator support.

// pointer decay: when raw C-style arrays are passed to functions by value they lose the size of the array. 
// if we pass the array by pointer or reference along with the size, we would have to manually update each time the size is changed.

int main() {

    // declaration of a std::array container
    std::array<int, 5> arr = {1,2,3,4,5};
    
    // printing all the elements of the array using for-each
    std::cout << "Array Elements: ";
    for(const int& elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // accessing elememts using the [] operator - no bound checks
    std::cout << arr[2] << std::endl;
    // this allows access but prints garbage value
    std::cout << arr[6] << std::endl;
    // trying to modify the garbage value - successful (UNDEFINED BEHAVIOUR)
    arr[6] = 234;
    std::cout << arr[6] << std::endl;

    // accessing elements with bound checking - at()
    std::cout << arr.at(3) << std::endl;
    // gives out_of_range exception - program stops here
    // std::cout << arr.at(7) << std::endl;

    // front and back provide access to the first and last elements
    std::cout << "Front element: " << arr.front() << std::endl;
    std::cout << "Back element: " << arr.back() << std::endl;

    // SPECIAL CASE: for a zero-length array (N == 0), in that case, array.begin() == array.end(), which is some unique value. 
    // The effect of calling front() or back() on a zero-sized array is undefined. 
    std::array<int, 0> zeroArr;
    // std::cout << arr.begin() << " $$$ " <<  arr.end() << std::endl;
    // std::cout << "Front element: " << zeroArr.front() << std::endl;
    // std::cout << "Back element: " << zeroArr.back() << std::endl;

    // data() - returns a C-style pointer pointing to the first element in the array 
    int* ptr = arr.data();
    std::cout << "Third element is: " << *(ptr + 3) << std::endl;
    // trying out of bounds access - successful (UNDEFINED BEHAVIOUR)
    std::cout << *(ptr + 6) << std::endl;

    // capacity checking for arrays
    std::cout << (arr.empty() ? "Array is empty" : "Array is not empty") << std::endl; ;
    std::cout << "Size of the array is: " << arr.size() << std::endl;
    std::cout << "Maximum possible size of the array is: " << arr.max_size() << std::endl;

    // operations
    // fill() - used to fill the entire array with a single value (linear complexity, depends on the size of the container)
    arr.fill(0);
    std::cout << "Array after filling elements: ";
    for(auto elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // swap() - used to swap the contents of two std::arrays 
    std::array<int, 4> a1{1,2,3,4}, a2{5,6,7,8};
    std::cout << "A1: ";
    for(int elem: a1) {
        std::cout << elem << " ";
    }
    std::cout << std::endl << "A2: ";
    for(int elem : a2) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    a1.swap(a2);
    
    std::cout << "A1: ";
    for(auto elem : a1) {
        std::cout << elem << " ";
    }
    std::cout << std::endl << "A2: ";
    for(auto elem : a2) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // creating multidimensional arrays
    std::array<std::array<int, 4>, 3> mat;      // creates a matrix with 3 rows and 4 columns

    // since the size is already determined here, we can easily initialise and manipulate using the [] operator
    for(int i=0; i<3; i++) {
        for(int j=0; j<4; j++) {
            mat[i][j] = (i+1) * (j+1);
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}