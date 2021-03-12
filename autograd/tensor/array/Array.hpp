#pragma once
#ifndef HEADER_FLAG
#define HEADER_FLAG

#include <cstdarg>
#include <iostream>
#include <exception>
#include <random>
#include <string>
#include <cstring>

// Forward declaration

//template <typename T, unsigned... DIM>
//std::ostream& operator<<(std::ostream& out, const Array<T, DIM...> array);

template<typename T, unsigned... DIM>
struct Array {
    // Struct stores my data
    private:
        unsigned int num_dimensions; // number of dimensions
        unsigned int data_size; // size of data
        unsigned int* dimensions; // array of dimension sizes
        unsigned int* one_d_dimensions; // array of dimensions for one D array
        T *data; // stores data
        
        /** 
         * Initialize the array
         * Args: Template arguments : < dimension sizes >
         */
        void unpack() {
            int size = 1;
            int dim_count = 0;
            auto values = {DIM...};
            for (unsigned s : values) {
                dim_count++;
                size *= s;
            }    

            if (dim_count != 0) {
                // Populate the multidimensional array dimensions and initialize the array
                dimensions = new unsigned int[dim_count];
                int count = 0;
                for (unsigned s : values) {
                    dimensions[count] = s;
                    count += 1;
                }

                // Initialize array
                data = new T[size];
                data_size = size;
                num_dimensions = dim_count;
            } else {
                data = NULL;
                dimensions = NULL;
            }
        }

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
        inline T& operator[](unsigned x) {
            return data[x];
        }
        const inline T& operator[](unsigned x) const {
            return data[x];
        }
        inline T* item() const {
            return data;
        }
        
        /** 
         * Constructor for the array
         * Args: Number of dimensions, < dimension sizes >
         */
        Array() {
            unpack();
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
        // Returns dimension array
        unsigned int* getdimarray() const {
            return dimensions;
        }
        // Return one dimension flattened array 
        unsigned int* getone_d_dimarray() const {
            return one_d_dimensions;
        }
        /** 
         * Print dimension array
         */ 
        inline void print_dims() const {
            for (int i=0; i<num_dimensions; ++i) {
                std::cout << "Dimension number " << i << " and the size is: " << dimensions[i] << std::endl; 
            }
        }
        /** 
         * Fills the array with 1s
         */
        inline void ones() const {
            for (int i=0; i<data_size; ++i) {
                data[i] = T (1);
            }
        }
        /**
         * Fills the array with random numbers generated off a normal distribution
         * with, Mean=0.0, SD=0.1
         */ 
        inline void randn() const {
            std::default_random_engine generator;
            std::normal_distribution<T> distribution(0.0, 1.0);
            for (int i=0; i<data_size; ++i) {
                data[i] = distribution(generator);
            }
        }
        /**
         * Reshape the array in place, by changing dimension mapping
         * of the 1D array to the N-D array
         * Args: Number of dimensions, < dimension sizes >
         */
        inline void reshape(unsigned dims, ...) {
            unsigned int* new_dimensions = new unsigned int[dims];
            va_list args;
            va_start (args, dims);
            unsigned int new_size = 1;
            for (int i=0; i<dims; ++i) {
                new_dimensions[i] = va_arg(args, unsigned int);
                new_size *= new_dimensions[i];
            }
            va_end(args);
            if (new_size != data_size) {
                std::cerr << "Size mismatch for original array of size: " << data_size << std::endl;
                exit(EXIT_FAILURE);
            }
            delete[] dimensions;
            delete[] one_d_dimensions;
            num_dimensions = dims;
            dimensions = NULL;
            one_d_dimensions = NULL;
            dimensions = new unsigned int[dims];
            one_d_dimensions = new unsigned int[dims];
            memcpy(dimensions, new_dimensions, sizeof(unsigned int) * dims);

            // Set correct multiplicative dimensions for flattening array
            one_d_dimensions[dims-1] = dimensions[dims-1];
            for (int a=dims-2; a>=0; --a) {
                one_d_dimensions[a] = dimensions[a+1] * dimensions[a];
            }
        }
        // Print out array
        //friend std::ostream& operator<<<T>(std::ostream& out, const Array array);
};

#endif