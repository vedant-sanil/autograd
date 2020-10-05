#include <iostream>
#include <cstdarg>

#include "Array.hpp"

int main() {
    Array<double> arr1 = Array<double>(3,3,3,3);
    arr1.ones();
    std::cout << arr1 << std::endl;
    arr1.~Array();
    return 0;
}