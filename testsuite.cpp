#include <iostream>
#include <vector>

#include "Array.hpp"

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
    Array<double, 3,3> data = Array<double,3,3>();
    std::cout << data.numdim() << std::endl;
    std::cout << 
    //cout << 
    /*
    arr1.randn();
    std::cout << arr1 << std::endl;
    arr1.reshape(2,3,9);
    std::cout << arr1 << std::endl;
    arr1.~Array();
    */
    return 0;
}