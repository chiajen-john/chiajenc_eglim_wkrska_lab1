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
#define STRIDE 32
#define MAX_STRIDES DATA_SIZE/STRIDE
#define MAX_CALLS MAX_STRIDES/256-1 // number of grouped calls that can be made ()

#define READ16(temp, arr, index) \
    temp = arr[index + STRIDE*0x0]; \
    temp = arr[index + STRIDE*0x1]; \
    temp = arr[index + STRIDE*0x2]; \
    temp = arr[index + STRIDE*0x3]; \
    temp = arr[index + STRIDE*0x4]; \
    temp = arr[index + STRIDE*0x5]; \
    temp = arr[index + STRIDE*0x6]; \
    temp = arr[index + STRIDE*0x7]; \
    temp = arr[index + STRIDE*0x8]; \
    temp = arr[index + STRIDE*0x9]; \
    temp = arr[index + STRIDE*0xA]; \
    temp = arr[index + STRIDE*0xB]; \
    temp = arr[index + STRIDE*0xC]; \
    temp = arr[index + STRIDE*0xD]; \
    temp = arr[index + STRIDE*0xE]; \
    temp = arr[index + STRIDE*0xF];

#define READ256(temp, arr, index) \
    READ256(temp, arr, index*0x000); \
    READ256(temp, arr, index*0x100); \
    READ256(temp, arr, index*0x200); \
    READ256(temp, arr, index*0x300); \
    READ256(temp, arr, index*0x400); \
    READ256(temp, arr, index*0x500); \
    READ256(temp, arr, index*0x600); \
    READ256(temp, arr, index*0x700); \
    READ256(temp, arr, index*0x800); \
    READ256(temp, arr, index*0x900); \
    READ256(temp, arr, index*0xA00); \
    READ256(temp, arr, index*0xB00); \
    READ256(temp, arr, index*0xC00); \
    READ256(temp, arr, index*0xD00); \
    READ256(temp, arr, index*0xE00); \
    READ256(temp, arr, index*0xF00);



extern "C" {
void krnl_exp3(const int *in   // Read-Only Matrix
) 
    {
        int temp = 0;
        for (int i = 0; i < stride; i++) {
            for (int j = 0; j < MAX_CALLS; j++) {
                READ256(temp, in, i);
            }
        }
    }
}
