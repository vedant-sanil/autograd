#include <iostream>
#include <cstdarg>

#include "Array.hpp"

void f(int x, ...) {
    va_list args;
    va_start (args, x);
    for (int i=0; i<x; ++i) {
        std::cout << va_arg(args, int) << std::endl;
    }
}

int main() {
    Array<double> arr1 = Array<double>(2,3,3,3);
    arr1(0,0,0) = 1.32;
    std::cout<< "Here" << std::endl;
    arr1(0,0,1) = 1.48;
    std::cout<< "Here" << std::endl;
    arr1(0,0,2) = 1.56;
    std::cout<< "Here" << std::endl;
    arr1(0,1,0) = 1.64; 
    std::cout<< "Here" << std::endl;
    arr1(0,1,1) = 2.18;
    std::cout<< "Here" << std::endl;
    arr1(0,1,2) = 1.77;
    std::cout<< "Here" << std::endl;
    arr1(0,2,0) = 1.723523;
    std::cout<< "Here" << std::endl;
    arr1(1,2,2) = 1.412523;
    std::cout<< "Here" << std::endl;
    arr1.print_dims();
    std::cout << "Works" << std::endl; 
    std::cout << arr1.size() << std::endl;
    std::cout << arr1.dimsize(0) << std::endl;
    //std::cout << arr1(1,2) << std::endl;
    //std::cout << arr1.datasize() << std::endl;
    //std::cout << arr1.size() << std::endl;
    arr1.~Array();
    return 0;
}