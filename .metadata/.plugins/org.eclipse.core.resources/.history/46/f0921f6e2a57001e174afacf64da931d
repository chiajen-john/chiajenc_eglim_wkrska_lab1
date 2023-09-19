//------------------------------------------------------------------------------
//
// kernel:  exp1b
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
const unsigned int c_len = DATA_DIM / BUFFER_SIZE; // this MUST be a whole number
const unsigned int c_size = BUFFER_SIZE;
const unsigned int c_num = DATA_DIM

extern "C" {
void krnl_exp1b(const float *in        // Read-Only Matrix
) 
    {
        float v_buffer[BUFFER_SIZE];   // Local memory to store vector

	    for (int i = 0; i < DATA_DIM; i++) { // iterates columns
            #pragma HLS LOOP_TRIPCOUNT min=c_num max=c_num
            int num_chunks
            for (int j = 0; j < DATA_DIM; j += BUFFER_SIZE) { // increments chunmk window
                #pragma HLS LOOP_TRIPCOUNT min=c_len max=c_len
                int chunk_size = BUFFER_SIZE;
                read1: for (int k = 0; k < chunk_size; k++) {
                    #pragma HLS LOOP_TRIPCOUNT min=c_size max=c_size
                    v_buffer[k] = in[(i + ((j+k)*DATA_DIM))];
                }
            }
        }
    }
}
