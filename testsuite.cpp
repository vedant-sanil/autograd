#include <iostream>
#include <cstdarg>

#include "Array.hpp"

int main() {
    Array<double> arr1 = Array<double>(3,3,3,3);
    arr1(2,2,2) = 3.2341;
    arr1.~Array();
    return 0;
}