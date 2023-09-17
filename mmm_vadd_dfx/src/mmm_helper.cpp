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

/*
 * CMU 18643 Fall 2022 Lab1 Exercise
 */

#include "mmm_helper.h"
#include <sys/time.h>

// Allocate memory on device and map pointers into the host
void mmm_allocate_mem (cl_object &cl_obj, krnl_object &krnl_obj, float **ptr_a, float **ptr_b, float **ptr_result, int size_in_bytes) {
    cl_int err;

    // These commands will allocate memory on the Device. The cl::Buffer objects can
    // be used to reference the memory locations on the device.
    OCL_CHECK(err, krnl_obj.buffers.emplace_back(cl_obj.context, CL_MEM_READ_ONLY, size_in_bytes, nullptr, &err)); // in1
    OCL_CHECK(err, krnl_obj.buffers.emplace_back(cl_obj.context, CL_MEM_READ_ONLY, size_in_bytes, nullptr, &err)); // in2
    OCL_CHECK(err, krnl_obj.buffers.emplace_back(cl_obj.context, CL_MEM_READ_WRITE, size_in_bytes, nullptr, &err)); // out, needs to be read/write

    cl::Buffer *buffer_a = &krnl_obj.buffers[0];
    cl::Buffer *buffer_b = &krnl_obj.buffers[1];
    cl::Buffer *buffer_result = &krnl_obj.buffers[2];

    //We then need to map our OpenCL buffers to get the pointers
    OCL_CHECK(err, (*ptr_a) = (float*)cl_obj.q.enqueueMapBuffer (*buffer_a , CL_TRUE , CL_MAP_WRITE , 0, size_in_bytes, NULL, NULL, &err));
    OCL_CHECK(err, (*ptr_b) = (float*)cl_obj.q.enqueueMapBuffer (*buffer_b , CL_TRUE , CL_MAP_WRITE , 0, size_in_bytes, NULL, NULL, &err));
    OCL_CHECK(err, (*ptr_result) = (float*)cl_obj.q.enqueueMapBuffer (*buffer_result , CL_TRUE , CL_MAP_READ , 0, size_in_bytes, NULL, NULL, &err)); // pointer to result out, should be read???

    // std::cout << "TODO: Alloate memory for results matrix and map ptr_result" << std::endl;
}

// Unmap device memory when done
void mmm_deallocate_mem (cl_object &cl_obj, krnl_object &krnl_obj, float *ptr_a, float *ptr_b, float *ptr_result) {
    cl_int err;

    cl::Buffer *buffer_a = &krnl_obj.buffers[0];
    cl::Buffer *buffer_b = &krnl_obj.buffers[1];
    cl::Buffer *buffer_result = &krnl_obj.buffers[2];

    OCL_CHECK(err, err = cl_obj.q.enqueueUnmapMemObject(*buffer_a , ptr_a));
    OCL_CHECK(err, err = cl_obj.q.enqueueUnmapMemObject(*buffer_b , ptr_b));
    OCL_CHECK(err, err = cl_obj.q.enqueueUnmapMemObject(*buffer_result , ptr_result));
    OCL_CHECK(err, err = cl_obj.q.finish());
}

// Set kernel arguments and execute it
void mmm_run_kernel(cl_object &cl_obj, krnl_object &krnl_obj, int dim) {
    cl_int err;

    // Copied directly from vadd example
    cl::Buffer *buffer_a = &krnl_obj.buffers[0];
    cl::Buffer *buffer_b = &krnl_obj.buffers[1];
    cl::Buffer *buffer_result = &krnl_obj.buffers[2];
    
    std::cout << "Running kernel " << krnl_obj.name << "..." << std::endl;

    // Copied directly from vadd example
    int narg=0;
    OCL_CHECK(err, err = krnl_obj.krnl.setArg(narg++, *buffer_a));
    OCL_CHECK(err, err = krnl_obj.krnl.setArg(narg++, *buffer_b));
    OCL_CHECK(err, err = krnl_obj.krnl.setArg(narg++, *buffer_result));
    OCL_CHECK(err, err = krnl_obj.krnl.setArg(narg++, dim));
    
    std::cout << "Args Set" << std::endl;

    /* Measure time from start of data loading to end of result downloading, and for just the time of execution
        (Mostly copied from lab 0 starter code)
    */
    struct timeval start_time_full, end_time_full, start_time_compute, end_time_compute;
    // Get "full" runtime start time
    gettimeofday(&start_time_full, NULL);
    std::cout << "Start 1 captured" << std::endl;

    // Queue migrate data to kernel
    OCL_CHECK(err, err = cl_obj.q.enqueueMigrateMemObjects({*buffer_a, *buffer_b},0/* 0 means from host*/));
    OCL_CHECK(err, cl_obj.q.finish());

    // Get "compute" runtime start time
    gettimeofday(&start_time_compute, NULL);
    std::cout << "Data loaded" << std::endl;
    std::cout << "Start 2 captured" << std::endl;

    // Queue start of kernel, wait until finished
    OCL_CHECK(err, err = cl_obj.q.enqueueTask(krnl_obj.krnl));
    OCL_CHECK(err, cl_obj.q.finish());

    // Get "compute" runtime end time
    gettimeofday(&end_time_compute, NULL);
    std::cout << "Execution Finished" << std::endl;
    std::cout << "End 2 captured" << std::endl;

    // Queue migrate data from kernel, wait until finished
    OCL_CHECK(err, cl_obj.q.enqueueMigrateMemObjects({*buffer_result}, CL_MIGRATE_MEM_OBJECT_HOST));
    OCL_CHECK(err, cl_obj.q.finish());

    // Get "full" runtime end time
    gettimeofday(&end_time_full, NULL);
    std::cout << "End 1 captured" << std::endl;
    std::cout << "Result Loaded" << std::endl;
    std::cout << "Kernel Finished" << std::endl;

    // Print runtimes
    double timeusec_full = (end_time_full.tv_sec - start_time_full.tv_sec) * 1e6 +
                    (end_time_full.tv_usec - start_time_full.tv_usec);
    double timeusec_compute = (end_time_compute.tv_sec - start_time_compute.tv_sec) * 1e6 +
                    (end_time_compute.tv_usec - start_time_compute.tv_usec);

    std::cout << "End-to-end runtime: " << timeusec_full << std::endl;
    std::cout << "Arithmetic runtime: " << timeusec_compute << std::endl;
}

/*
 * The below very neat implementation of float eqaul is taken from
 * http://floating-point-gui.de/errors/comparison/
 *
 * Published at floating-point-gui.de under the Creative Commons
 * Attribution License (BY)
 * http://creativecommons.org/licenses/by/3.0/
 */
#include <math.h>
#include <float.h>
#define EPSILON (1e-4)

int nearlyEqual(float a, float b) {
    float absA = fabs(a);
    float absB = fabs(b);
    float diff = fabs(a - b);

    if (a == b) { // shortcut, handles infinities
        return 1;
    } else if (a == 0 || b == 0 || diff < FLT_MIN) {
        // a or b is zero or both are extremely close to it
        // relative error is less meaningful here
        return diff < (EPSILON * FLT_MIN);
    } else { // use relative error
        return diff / fmin((absA + absB), FLT_MAX) < EPSILON;
    }
}

static const std::string mmm_error_message =
    "Error: Result mismatch:\n"
    "i = %d CPU result = %f Device result = %f\n";

// Verification functions
int mmm_check(float *ptr_a, float *ptr_b, float *ptr_result, int dim) {
    std::cout << "Verifying mmm result..." << std::endl;

    //Verify the result
    int match = 0;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            float host_result = 0;
            for (int k = 0; k < dim; k++) {
                host_result += ptr_a[i * dim + k] * ptr_b[k * dim + j];
            }
            if (!nearlyEqual(ptr_result[i * dim + j], host_result)) {
                printf(mmm_error_message.c_str(), i, host_result, ptr_result[i]);
                match = 1;
                break;
            }
        }
    }

    return match;
}
