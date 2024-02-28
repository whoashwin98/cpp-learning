// practice file for clearing doubts
#include <iostream>
#include <array>

int main() {
    std::array<int, 5> arr{1,2,3,4,5}; 

    // accessing using the operator [] leads to undefined behaviour when the index given is out of bounds - program runs successfully
    std::cout << arr[8] << std::endl;

    // accessing any out of range element using the at() function would result in an exception being thrown - halts program execution
    std::cout << arr.at(3) << std::endl;
    std::cout << "This line is printed if there is no exception in the previous line!" << std::endl;

    // data function returns the underlying raw pointer used to store the elements
    int* rawArr = arr.data();  

    std::cout << rawArr[1] << std::endl;

    // multidimensional array - we can directly set values here since the size of the arrays is known and decided
    std::array<std::array<int, 4>, 3> mat;

    for(int i=0; i<mat.size(); i++) {
        for(int j=0; j<mat[0].size(); j++) {
            mat[i][j] = i + j;
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // trying to create a fixed size std::array of pointers - need to be careful about allocating memory and de-allocating it when the work is over
    std::array<int*, 3> ptrs;
    for(int i=0; i<3; i++) {
        ptrs[i] = new int[(i+1) * 5];
        for(int j = 0; j < (5*i + 5); j++) {
            ptrs[i][j] = (i+1) * (j+1);
            std::cout << ptrs[i][j] << " ";
        }
        delete[] ptrs[i];
        std::cout << std::endl;

    }

    return 0;
}