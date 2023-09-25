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

#define NUM_ITER 4096

// 4096 * 4096 = 2^24 elements in array
// use lower 24 bits of random int as address
// can just AND with 0x00FFFFFF
#define ADDR_AND 16777215

extern "C" {

int xorshift(int num) {
  num ^= num << 13;
  num ^= num >> 17;
  num ^= num << 5;
  return num;
}

void krnl_exp3(const int *in,   // Read-Only Matrix
               int *out) {
  int addr = ADDR_AND & 852129405; 
  int accum = -1877593432;
  int temp;

  // TODO: initialize memory w/ random values before calling kernel
  for (int i = 0; i < NUM_ITER; i++) {
    temp = in[addr];
    addr = ADDR_AND & xorshift(temp);
    accum ^= temp;
  }

  out[0] = accum;
}
}
