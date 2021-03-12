#include <iostream>
#include <vector>

#include "tensor/array/Array.h"

/*
template<class T, unsigned... dims>
struct Array {
    public:
    std::vector<unsigned> dimesnions;
    void print_values() {
        auto values = {dims...};
        for (auto s : values) {
            std::cout << s << std::endl;
        }
    } 
        //T *data = new T[5]; 

};
*/

int main() {
    Array<double, 3,3> arr = Array<double,3,3>();
    arr.randn();

    std::cout << arr[0];

    //arr = {{1,2,3}, {4,5,6}, {7,8,9}};
    //struct Array arrs = {1,2,3};

    //cout << 
    /*
    arr1.randn();
    std::cout << arr1 << std::endl;
    arr1.reshape(2,3,9);
    */
    //std::cout << arr << std::endl;
    
    return 0;
}