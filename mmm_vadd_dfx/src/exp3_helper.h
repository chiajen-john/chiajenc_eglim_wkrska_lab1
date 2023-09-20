#pragma once

#include "utils.h"

// Allocate memory on device and map pointers into the host 
void exp3_allocate_mem(cl_object &cl_obj, krnl_object &krnl_obj, int **ptr_in, int size_in_bytes);

// Unmap device memory when done
void exp3_deallocate_mem(cl_object &cl_obj, krnl_object &krnl_obj, int *ptr_in);

// Set kernel arguments and execute it 
void exp3_run_kernel(cl_object &cl_obj, krnl_object &krnl_obj);