/* NOTE: I didn't make any changes to this beyond removing the MMM checksum*/

#include "exp3_helper.h"
#include <sys/time.h>

// Allocate memory on device and map pointers into the host
void exp3_allocate_mem (cl_object &cl_obj, krnl_object &krnl_obj, int **ptr_in, int size_in_bytes) {
    cl_int err;

    // These commands will allocate memory on the Device. The cl::Buffer objects can
    // be used to reference the memory locations on the device.
    OCL_CHECK(err, krnl_obj.buffers.emplace_back(cl_obj.context, CL_MEM_READ_ONLY, size_in_bytes, nullptr, &err)); // in1
    
    cl::Buffer *buffer_in = &krnl_obj.buffers[0];
    
    //We then need to map our OpenCL buffers to get the pointers
    OCL_CHECK(err, (*ptr_in) = (int*)cl_obj.q.enqueueMapBuffer (*buffer_in , CL_TRUE , CL_MAP_WRITE , 0, size_in_bytes, NULL, NULL, &err));
}

// Unmap device memory when done
void exp3_deallocate_mem (cl_object &cl_obj, krnl_object &krnl_obj, int *ptr_in) {
    cl_int err;

    cl::Buffer *buffer_in = &krnl_obj.buffers[0];
    
    OCL_CHECK(err, err = cl_obj.q.enqueueUnmapMemObject(*buffer_in , ptr_in));
    OCL_CHECK(err, err = cl_obj.q.finish());
}

// Set kernel arguments and execute it
void exp3_run_kernel(cl_object &cl_obj, krnl_object &krnl_obj) {
    cl_int err;

    // Copied directly from vadd example
    cl::Buffer *buffer_in = &krnl_obj.buffers[0];
    
    std::cout << "Running kernel " << krnl_obj.name << "..." << std::endl;

    // Copied directly from vadd example
    int narg=0;
    OCL_CHECK(err, err = krnl_obj.krnl.setArg(narg++, *buffer_in));
    
    std::cout << "Args Set" << std::endl;

    /* Measure time from start of data loading to end of result downloading, and for just the time of execution
        (Mostly copied from lab 0 starter code)
    */
    struct timeval start_time, end_time;

    // Queue migrate data to kernel
    OCL_CHECK(err, err = cl_obj.q.enqueueMigrateMemObjects({*buffer_in},0/* 0 means from host*/));
    OCL_CHECK(err, cl_obj.q.finish());

    // Get "compute" runtime start time
    gettimeofday(&start_time, NULL);
    std::cout << "Data loaded" << std::endl;
    std::cout << "Start captured" << std::endl;

    // Queue start of kernel, wait until finished
    OCL_CHECK(err, err = cl_obj.q.enqueueTask(krnl_obj.krnl));
    OCL_CHECK(err, cl_obj.q.finish());

    // Get "compute" runtime end time
    gettimeofday(&end_time, NULL);
    std::cout << "Execution Finished" << std::endl;
    std::cout << "End captured" << std::endl;
    std::cout << "Result Loaded" << std::endl;
    std::cout << "Kernel Finished" << std::endl;

    // Print runtimes
    double timeusec = (end_time.tv_sec - start_time.tv_sec) * 1e6 +
                    (end_time.tv_usec - start_time.tv_usec);

    std::cout << "Arithmetic runtime: " << timeusec << std::endl;
}
