//------------------------------------------------------------------------------
//
// kernel:  exp1a
//
// Purpose: 
//
/*
    Matrix Multiplication Kernel Implementation
    Arguments:
        in    (input)     --> Input Matrix
        size  (input)     --> Dimension of Matrix in Integer
 */

// Update values when needed!!
#define BUFFER_SIZE 256
#define DATA_DIM 4096
#define DATA_SIZE DATA_DIM*DATA_DIM

//TRIPCOUNT identifier
const unsigned int c_len = DATA_SIZE / BUFFER_SIZE;
const unsigned int c_size = BUFFER_SIZE;

/* Create pre-populated array (not sure if this works)
   Credit: https://stackoverflow.com/questions/2978259/programmatically-create-static-arrays-at-compile-time-in-c

   Example Usage:

   const size_t count = 5;
   typedef generate_array<count, MetaFunc>::result A;   
   for (size_t i=0; i<count; ++i) 
       std::cout << A::data[i] << "\n";
   */
template<size_t index> struct MetaFunc { 
    enum { value = index + 1 }; 
};

extern "C" {
void krnl_exp2a(const float *in,        // Read-Only Matrix
        int size                      // Dimension in integer
) 
    {
        typedef generate_array<c_size, MetaFunc>::result v_buffer;

	    for (int i = 0; i < size*size; i += BUFFER_SIZE) {
            #pragma HLS LOOP_TRIPCOUNT min=c_len max=c_len
            int chunk_size = BUFFER_SIZE;

            read1: for (int j = 0; j < chunk_size; j++) {
                #pragma HLS LOOP_TRIPCOUNT min=c_size max=c_size
                out[i+j] = v_buffer::data[j];
            }
        }
    }
}
