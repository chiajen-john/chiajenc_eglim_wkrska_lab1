//------------------------------------------------------------------------------
//
// kernel:  exp1b
//
// Purpose: Determine the memory bandwidth by reading column-by-column
//

// Update values when needed!!
#define BUFFER_SIZE 64
#define DATA_DIM 4096

extern "C" {
void krnl_exp1b(const float *in        // Read-Only Matrix
) 
    {
        volatile float c[BUFFER_SIZE]; // local variable to store matrix entry

	    for (int i = 0; i < DATA_DIM; i++) { // iterates columns
            for (int j = 0; j < DATA_DIM; j++) {
            	c[j % BUFFER_SIZE] = in[i + j * DATA_DIM ]; // in[j][i]
            }
        }
    }
}
