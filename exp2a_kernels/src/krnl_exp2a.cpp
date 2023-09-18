//------------------------------------------------------------------------------
//
// kernel:  exp2a
//
// Purpose: 
//
/*
    Matrix Multiplication Kernel Implementation
    Arguments:
        out   (output)    --> Output Matrix
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
void krnl_exp2a(float *out,             // Output Result
        int size                      // Dimension in integer
) 
    {
	    float v_buffer[BUFFER_SIZE];
        // Init Buffer
        int chunk_size = BUFFER_SIZE;
        for (int b = 0; b < chunk_size; b++) {
            v_buffer = 
        }
        return 0
    }
}
