//------------------------------------------------------------------------------
//
// kernel:  exp3
//
// Purpose: 
//
/*
    Matrix Multiplication Kernel Implementation
    Arguments:
        in1   (input)     --> Input Matrix1
        in2   (input)     --> Input Matrix2
        out_r (output)    --> Output Matrix
        size  (input)     --> Dimension of Matrix in Integer
 */

#define DATA_DIM 4096
#define DATA_SIZE DATA_DIM*DATA_DIM
#define STRIDE 256

extern "C" {
void krnl_exp3(const int *in   // Read-Only Matrix
) 
    {
        volatile int temp = 0; // Ensures the variable is written to

        #pragma unroll
        for (int i = 0; i < STRIDE; i++) { // for every starting position [0, STRIDE)...
            #pragma unroll
            for (int j = i; j < DATA_SIZE; j += STRIDE) { // Read STRIDE 
                temp = in[j];
            }
        }
    }
}
