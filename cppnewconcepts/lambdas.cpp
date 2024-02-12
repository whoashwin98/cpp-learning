// lambdas in CPP
#include <iostream>
#include <vector>
#include <algorithm>

// lambdas are anonymous functions which can be defined inline within your code. they provide a concise
// way to create function objects without the need to declare and define them separately 
// particularly useful when we have to pass short, one-off functions (like predicates to STL algorithms)

// the syntax is described below with each component explained in detail
// [capture-list] (parameter-list) -> return-type { body }

// capture-list provides a way to pass variables that belong to the surrounding scope to the lambda
// they allow captures to be passed by value (=) or by reference (&)
// parameter-list consists of the parameters which the lambda will use in its body as a part of its own funcitonality
// -> return-type is used to specify the return type explicitly, which can also be omitted

// a normal function to multiply two numbers
int multiplyBy5(int x) {
    return x * 5;
}

int main() {
    std::vector<int> v{1,2,3,4,5,6,7,8,9,10};
    /*
    std::cout << "Before transform: ";
    for(auto it : v) std::cout << it << " ";
    std::cout << std::endl;
    
    // note that we had to write a dedicated function for performing a simple operation
    std::transform(v.begin(), v.end(), v.begin(), multiplyBy5);
    std::cout << "After transform using normal function: ";
    for(auto it : v) std::cout << it << " ";
    std::cout << std::endl;

    // we can do the same thing using lambda
    std::transform(v.begin(), v.end(), v.begin(), [](int x) -> int { return x * 10; });
    std::cout << "After transform using lambda function: ";
    for(auto it : v) std::cout << it << " ";
    std::cout << std::endl;

    */
   
    // all possible types of lambda functions
    int x = 10, y = 15;

    auto lambda1 = [](){ std::cout << "No args, no return type!" << std::endl; };

    // by providing the mutable keyword, we are able to modify the capture values without which we are not
    // even allowed to modify them inside the lambda's body. changes are not reflected in the main variables   
    auto lambda2 = [x,y]()mutable{ x+= 18; y-=13; std::cout << "Capture values: " << x << " " << y << std::endl; };
    
    // passing by reference, whatever changes are made are reflected in the main variables
    auto lambda3 = [&x,&y](){ x+= 18; y-=13; std::cout << "Capture values: " << x << " " << y << std::endl; };

    auto lambda4 = [](int x, int y) { return x+y+12; };

    lambda1();
    std::cout << "Capture values passed by value: " << std::endl;
    lambda2();
    std::cout << "Lambda with return value and parameters: " << lambda4(x, y) << std::endl;
    std::cout << "Capture values passed by reference: " << std::endl;
    lambda3();
    std::cout << "Lambda with return value and parameters: " << lambda4(x, y) << std::endl;

    return 0;
}