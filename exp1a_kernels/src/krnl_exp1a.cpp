//------------------------------------------------------------------------------
//
// kernel:  exp1a
//
// Purpose: Determine memory bandwidth by reading row-by-row
//

// Update values when needed!!
#define BUFFER_SIZE 256
#define DATA_DIM 4096
#define DATA_SIZE DATA_DIM*DATA_DIM

const unsigned int c_len = DATA_SIZE / BUFFER_SIZE;
const unsigned int c_size = BUFFER_SIZE;

extern "C" {
void krnl_exp1a(const float *in,        // Read-Only Matrix
		float *out
) 
    {
		int chunk_size;
		volatile float v_buffer[BUFFER_SIZE];   // Local memory to store vector

        for (int k = 0; k < DATA_DIM; k += 1) {
        	for (int i = 0; i < DATA_DIM; i += BUFFER_SIZE) {
        		#pragma HLS LOOP_TRIPCOUNT min=c_len max=c_len
        	    chunk_size = BUFFER_SIZE;
        	    // read through a row by chunk_size
        	    read1: for (int j = 0; j < chunk_size; j++) {
        	    	#pragma HLS LOOP_TRIPCOUNT min=c_size max=c_size
        	        	v_buffer[j] = in[k * DATA_DIM + i + j]; // in[k][i * BUFFER_SIZE + j]
        	    }
        	    for (int j = 0; j < chunk_size; j++) {
        	    	out[0] += v_buffer[j]; // accumulate
        	    }

        	}
        }
    }
}
