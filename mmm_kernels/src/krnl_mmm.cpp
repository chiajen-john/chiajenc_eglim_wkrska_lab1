/****************************************************************
 * Copyright (c) 2017~2022, 18-643 Course Staff, CMU
 * All rights reserved.

 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:

 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.

 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.

 * The views and conclusions contained in the software and
 * documentation are those of the authors and should not be
 * interpreted as representing official policies, either expressed or
 * implied, of the FreeBSD Project.
 ****************************************************************/

//------------------------------------------------------------------------------
//
// kernel:  mmm
//
// Purpose: Demonstrate Matrix Multiplication Kernel
//
/*
    Matrix Multiplication Kernel Implementation
    Arguments:
        in1   (input)     --> Input Matrix1
        in2   (input)     --> Input Matrix2
        out_r (output)    --> Output Matrix
        size  (input)     --> Dimension of Matrix in Integer
 */

#define DATA_DIM 640 

extern "C" {
void krnl_mmm(const float *in1,  // Read-Only Matrix 1
        const float *in2,      // Read-Only Matrix 2
        float *out_r,          // Output Result
        int size) {



  //out_r[0] = in1[0];
	for (int k = 0; k < DATA_DIM; k += 1){
		for (int i = 0; i < DATA_DIM; i += 1) {
			for (int j = 0; j < DATA_DIM; j += 1) {
				out_r[i * DATA_DIM + j] += in1[i * DATA_DIM + k] * in2[k * DATA_DIM + j];
			}
		}
	}
}
}
