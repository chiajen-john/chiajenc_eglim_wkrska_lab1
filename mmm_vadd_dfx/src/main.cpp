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

#include "vadd_helper.h"
#define VADD_DIM 4096

#include "mmm_helper.h"
#define MMM_DIM 128


int main(int argc, char* argv[]) {

	// Hard coding xclbin filenames, ignoring command line arguments
    std::string xclbinFilename[3] = {
    		"binary_container_vadd.xclbin",
    		"binary_container_mmm.xclbin"
			// increase array size to add more container names
    };

    cl_object cl_obj;

    initialize_device(cl_obj);

    {
        // Read vadd
        read_xclbin(xclbinFilename[0], cl_obj.bins);

        krnl_object vadd_obj;
        vadd_obj.index = 0;
        vadd_obj.name = "krnl_vadd";

        int *ptr_a, *ptr_b, *ptr_result;

        program_kernel(cl_obj, vadd_obj);
        vadd_allocate_mem(cl_obj, vadd_obj, &ptr_a, &ptr_b, &ptr_result, VADD_DIM * sizeof(int));
        initialize_memory_int(ptr_a, VADD_DIM);
        initialize_memory_int(ptr_b, VADD_DIM);
        vadd_run_kernel(cl_obj, vadd_obj, VADD_DIM);
        int match = vadd_check(ptr_a, ptr_b, ptr_result, VADD_DIM);
        std::cout << "VADD TEST " << (match ? "FAILED" : "PASSED") << "\n" << std::endl;
        vadd_deallocate_mem(cl_obj, vadd_obj, ptr_a, ptr_b, ptr_result);
    }

    {
        // Read mmm
        read_xclbin(xclbinFilename[1], cl_obj.bins);

        krnl_object mmm_obj;
        mmm_obj.index = 1;
        mmm_obj.name = "krnl_mmm";

        float *ptr_a, *ptr_b, *ptr_result;

        int mmm_size = (argc>3) ? atoi(argv[argc-1]) : MMM_DIM;
        std::cout << "Size = " << mmm_size << std::endl;

        program_kernel(cl_obj, mmm_obj);
        mmm_allocate_mem(cl_obj, mmm_obj, &ptr_a, &ptr_b, &ptr_result, mmm_size * mmm_size * sizeof(float));
        initialize_memory_fp(ptr_a, mmm_size * mmm_size);
        initialize_memory_fp(ptr_b, mmm_size * mmm_size);
        mmm_run_kernel(cl_obj, mmm_obj, mmm_size);
        int match = mmm_check(ptr_a, ptr_b, ptr_result, mmm_size);
        std::cout << "MMM TEST " << (match ? "FAILED" : "PASSED") << "\n" << std::endl;
        mmm_deallocate_mem(cl_obj, mmm_obj, ptr_a, ptr_b, ptr_result);
    }

#if 0
    // Reuse this template to continue to develop Part 4
    {
        read_xclbin(xclbinFilename[?], cl_obj.bins);

        krnl_object xyz_obj;
        xyz_obj.index = ?;
        xyz_obj.name = "????";

        float *ptr_a, *ptr_b, *ptr_result;

        program_kernel(cl_obj, xyz_obj);
        mmm_allocate_mem(cl_obj, xyz_obj, &ptr_a, &ptr_b, &ptr_result, MMM_DIM * MMM_DIM * sizeof(float));
        initialize_memory_fp(ptr_a, MMM_DIM * MMM_DIM);
        initialize_memory_fp(ptr_b, MMM_DIM * MMM_DIM);
        mmm_run_kernel(cl_obj, xyz_obj, MMM_DIM);
        //int match = mmm_check(ptr_a, ptr_b, ptr_result, MMM_DIM);
        //std::cout << "MMM TEST " << (match ? "FAILED" : "PASSED") << "\n" << std::endl;
        mmm_deallocate_mem(cl_obj, xyz_obj, ptr_a, ptr_b, ptr_result);
    }
#endif
}
