// functors in CPP
#include <iostream>
#include <vector>
#include <algorithm>

/*
    IMPORTANT LINKS: 
    https://stackoverflow.com/questions/356950/what-are-c-functors-and-their-uses (FUNCTORS AND THEIR USES)
    https://stackoverflow.com/questions/6451866/why-use-functors-over-functions (WHY USE FUNCTORS OVER FUNCTIONS)

*/

// function objects or functors are objects that behave like functions. it overloads the operator(), which allows
// the classes to be invoked as if they were functions. they are a more flexible and powerful alternative
// to function pointers.

// not only do functors have functions, they also have member variables
// the most important property is that function objects are able to encapsulate states, which help maintain
// internal state between calls. 
// are able to reap all the benefits of object-oriented programming since it is a function object 

// use functors when you need stateful operations, custom behavior, polymorphism, or complex behavior 
// beyond simple function calls

// an example program to demonstrate the use of functors
class ThresholdFilter {
private:
    int threshold; // state: threshold value

public:
    ThresholdFilter(int threshold) : threshold(threshold) {}

    bool operator()(int num) const {
        return num < threshold;
    }

    int getThreshold() {
        return threshold;
    }

    void setThreshold(int newThreshold) {
        threshold = newThreshold;
    }
};

int main() {
    std::vector<int> numbers = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    ThresholdFilter filter(50);

    std::vector<int> filteredNumbers;
    for (int num : numbers) {
        if (filter(num)) {
            filteredNumbers.push_back(num);
        }
    }


    std::cout << "Current threshold: " << filter.getThreshold() << std::endl;
    std::cout << "Numbers below the threshold: ";
    for (int num : filteredNumbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    filter.setThreshold(70);
    filteredNumbers.clear();
    for (int num : numbers) {
        if (filter(num)) {
            filteredNumbers.push_back(num);
        }
    }

    std::cout << "Current threshold: " << filter.getThreshold() << std::endl;
    std::cout << "Numbers below the updated threshold: ";
    for (int num : filteredNumbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
