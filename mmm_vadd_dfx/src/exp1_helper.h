#pragma once

#include "utils.h"

// Allocate memory on device and map pointers into the host 
void exp1_allocate_mem(cl_object &cl_obj, krnl_object &krnl_obj, float **ptr_in, float **ptr_out, int size_in_bytes);

// Unmap device memory when done
void exp1_deallocate_mem(cl_object &cl_obj, krnl_object &krnl_obj, float *ptr_in, float *ptr_out);

// Set kernel arguments and execute it 
void exp1_run_kernel(cl_object &cl_obj, krnl_object &krnl_obj);
