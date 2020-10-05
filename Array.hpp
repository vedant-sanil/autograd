#pragma once
#ifndef HEADER_FLAG
#define HEADER_FLAG

#include <cstdarg>
#include <iostream>
#include <exception>

// Forward declaration
template <typename T>
struct Array;

template <typename T>
std::ostream& operator<<(std::ostream& out, const Array<T> array);

template<typename T>
struct Array {
    // Struct stores my data
    private:
        unsigned int num_dimensions; // number of dimensions
        unsigned int data_size; // size of data
        unsigned int* dimensions; // array of dimension sizes
        unsigned int* one_d_dimensions; // array of dimensions for one D array
        T* data; // stores data

    public:
        unsigned int* shape;
        static T aoob; 
        //static const T aoob;
        // Accessor methods
        inline unsigned numdim() const {
            return num_dimensions;
        }
        inline unsigned dimsize(unsigned x) const {
            return dimensions[x];
        }
        // No argument constructor
        Array() {
            num_dimensions = 0;
            data_size = 0;
            dimensions = NULL;
            one_d_dimensions = NULL;
            data = NULL;
        }
        // Constructor for the array
        // Args: Number of dimensions, < dimension sizes >
        Array(unsigned ndim, ...) {
            num_dimensions = ndim;
            if (ndim==0) {
                dimensions = NULL;
                one_d_dimensions = NULL;
                data = NULL;
                data_size = 0;
            } else {
                dimensions = new unsigned int[ndim];
                one_d_dimensions = new unsigned int[ndim];
                va_list args;
                va_start (args, ndim);
                unsigned size=1;
                for (int a=0; a<ndim; ++a) {
                    dimensions[a] = va_arg(args, unsigned int);
                    size*=dimensions[a];
                }
                data = new T[size];
                data_size = size;
                va_end(args);

                // Set correct multiplicative dimensions for flattening array
                one_d_dimensions[ndim-1] = dimensions[ndim-1];
                for (int a=ndim-2; a>=0; --a) {
                    one_d_dimensions[a] = dimensions[a+1] * dimensions[a];
                }
            }
            shape = dimensions;
        }
        // Destructor
        ~Array() {
            delete[] dimensions;
            delete[] data;
        }       
        // Return a reference to the element at the current position
        // Operator () (x,y,z,....)
        T& operator()(unsigned x, ...) {
            unsigned int index=x, pos=0, dim=1, a=0;
            va_list args;
            va_start(args, x);
            for (;a<num_dimensions; ++a) {
                if ((a != 0) && (index=va_arg(args, unsigned int)) > dimensions[a]-1 || (x > dimensions[0]-1)) {
                    std::cerr << "Out of Range error" << std::endl;
                    exit(EXIT_FAILURE); // Change this to throw catch statements
                }
                if (a == num_dimensions-1) {
                    break;
                }
                dim = one_d_dimensions[a+1];
                pos += dim * index;
            }
            pos += index;
            va_end(args);
            return data[pos];
        }
        // Const correctness, TODO: Research on it
        const T& operator()(unsigned x, ...) const {
            unsigned int index=x, pos=0, dim=1, a=0;
            va_list args;
            va_start(args, x);
            for (;a<num_dimensions; ++a) {
                if ((a != 0) && (index=va_arg(args, unsigned int)) > dimensions[a]) {
                    std::cerr << "Out of Range error" << std::endl;
                    exit(EXIT_FAILURE);
                }
                if (a == num_dimensions-1) {
                    break;
                }
                dim = one_d_dimensions[a+1];
                pos += dim * index;
            }
            pos += index;
            va_end(args);
            if (pos >= data_size) {
                std::cerr << "Out of Range error" << std::endl;
                exit(EXIT_FAILURE);
            }
            return data[pos];
        }
        // Return size in bytes of the contained data
        inline int datasize() const {
            return data_size*sizeof(T);
        }
        // Returns the number of elements contained
        inline int size() const {
            return data_size;
        }
        // Print dimension array 
        inline void print_dims() const {
            for (int i=0; i<num_dimensions; ++i) {
                std::cout << "Dimension number " << i << " and the size is: " << dimensions[i] << std::endl; 
            }
        }
        // Fills the array with 1
        inline void ones() const {
            for (int i=0; i<data_size; ++i) {
                data[i] = T (1);
            }
        }
        // Print out array
        friend std::ostream& operator<<<T>(std::ostream& out, const Array array);
};

template <typename T>
std::ostream& operator<< (std::ostream &out, const Array<T> array) {
    for (int i=0; i<array.numdim(); ++i) {
        out << i << std::endl;
    }
    return out;
};

#endif