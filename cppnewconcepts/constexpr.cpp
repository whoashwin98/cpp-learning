// constexpr in CPP
#include <iostream>
#include <random>

// constexpr keyword indicates that a certain function or object can be evaluated at compile time rather than 
// run time, whenever it is possible to do so - reducing runtime overheads - helps because some computations might be 
// known already during compile time, and calling functions or objects for them during compile time reduces overhead
// and improves performance

constexpr int factorial(int n) {
    if(n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

// non-constexpr function
int add(int a, int b) {
    return a + b;
}

// constexpr function calling a non-constexpr function
constexpr int multiply(int a, int b) {
    return add(a, b);
}

int main() {
    std::random_device rd;

    // since we are passing a non-constexpr function as an argument, this automatically implies that this particular
    // value will only be calculated at run time and not compile time
    int result = factorial(rd() % 6);
    std::cout << result << std::endl;

    // using the constexpr keyword explicitly here, ensures this value is computed at compile time
    // if this keyword is omitted here, the compiler might or might not evaluate this value at compile time (as it finds it necessary)
    constexpr int ans = factorial(7);
    std::cout << ans << std::endl;
    
    return 0;
}