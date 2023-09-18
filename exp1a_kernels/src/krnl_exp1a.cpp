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

extern "C" {
void krnl_exp1a(const float *in,        // Read-Only Matrix
        int size                      // Dimension in integer
) 
    {
        unsigned int v_buffer[BUFFER_SIZE];   // Local memory to store vector

	    for (int i = 0; i < size*size; i += BUFFER_SIZE) {
            #pragma HLS LOOP_TRIPCOUNT min=c_len max=c_len
            int chunk_size = BUFFER_SIZE;

            read1: for (int j = 0; j < chunk_size; j++) {
                #pragma HLS LOOP_TRIPCOUNT min=c_size max=c_size
                v_buffer[j] = in[i + j];
            }
        }
    }
}
