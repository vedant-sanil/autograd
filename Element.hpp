#pragma once
#ifndef HEADER_FLAG
#define HEADER_FLAG

#include <cstdarg>

template<typename T>
struct array {
    // Struct stores my data
    private:
        unsigned int num_dimensions; // number of dimensions
        unsigned int data_size; // size of data
        unsigned* dimensions; // array of dimension sizes
        T* data; // stores data

    public:
        static T aoob; 
        static const T aoob;
        // No argument constructor
        array() {
            num_dimensions = 0;
            data_size = 0;
            dimensions = NULL;
            data = NULL;
        }
        // Constructor for the array
        // Args: Number of dimensions, < dimension sizes >
        array(unsigned ndim, ...) {
            num_dimensions = ndim;
            if (ndim==0) {
                dimension = NULL;
                data = NULL;
                data_size = 0;
            } else {
                dimensions = new unsigned[ndim]
                va_list args;
                va_start (args, ndim);
                unsigned size=1;
                for (int a=0; a<ndim; ++a) {
                    dimensions[a] = va_arg(args, T);
                    size*=dimensions[a];
                }
                data = new T[size];
                data_size = size;
                va_end(args);
            }
        }
        // Destructor
        ~array() {
            delete[] dimensions;
            delete[] data;
        }       
        // Return a reference to the element at the current position
        // Operator () (x,y,z,....)
        T& operator()(unsigned x, ...) {
            unsigned index, pos=x, dim=1, a=0;
            va_list args;
            va_start(args, x);
            for (;a<num_dimensions; ++a) {
                if ((index=va_arg(args, unsigned)) > dimensions[a]){
                    return aoob;
                }
                dim *= dimensions[a];
                pos += index*dim;
            }
            va_end(args)
            return data[pos];
        }
        // Const correctness, TODO: Research on it
        const T& operator()(unsigned x, ...) const {
            unsigned index, pos=x, dim=1, a=0;
            va_list args;
            va_start(args, x);
            for (;a<num_dimensions; ++a) {
                if ((index=va_arg(args, unsigned)) > dimensions[a]){
                    return aoob;
                }
                dim *= dimensions[a];
                pos += index*dim;
            }
            va_end(args)
            return data[pos];
        }
        // Return size in bytes of the contained data
        inline int datasize() const {
            return data_size*sizeof(T);
        }
};

#endif