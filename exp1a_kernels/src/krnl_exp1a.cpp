//------------------------------------------------------------------------------
//
// kernel:  exp1a
//
// Purpose: Determine memory bandwidth by reading row-by-row
//

// Update values when needed!!
#define DATA_DIM 4096
#define DATA_SIZE DATA_DIM*DATA_DIM

extern "C" {
void krnl_exp1a(const float *in,        // Read-Only Matrix
		float *out
) 
    {
		float acc = 0;

        for (int k = 0; k < DATA_DIM; k += 1) {
			#pragma HLS unroll factor=16
        	for (int i = 0; i < DATA_DIM; i += 1) {
				#pragma HLS unroll factor=16
        		acc += in[k * DATA_DIM + i]; // in[k][i]
        	}
        }

        out[0] = acc;
    }
}
