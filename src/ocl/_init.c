/**
 * The MIT License (MIT)
 * 
 * Copyright (c) 2016 inkstack.info
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/*
 * _init.c
 *
 *  Created on: 2016-2-5
 *      Author: Halo9Pan
 */

#include "_init.h"

hpc_framework blas_framework;

cl_int
hpc_framework_initialize (void)
{
  printf ("Size of framework: %d\n", sizeof(blas_framework));

  cl_int err;
  /* Setup OpenCL environment. */
  err = clGetPlatformIDs (1, &blas_framework.platform.ocl, NULL);
  if (err != CL_SUCCESS)
	{
	  printf ("clGetPlatformIDs() failed with %d\n", err);
	  return err;
	}

  err = clGetDeviceIDs (blas_framework.platform.ocl, CL_DEVICE_TYPE_GPU, 1, &blas_framework.device.ocl, NULL);
  if (err != CL_SUCCESS)
	{
	  printf ("clGetDeviceIDs() failed with %d\n", err);
	  return err;
	}

  cl_context_properties properties[3] = { CL_CONTEXT_PLATFORM, blas_framework.platform.ocl, 0 };
  blas_framework.context.ocl = clCreateContext (properties, 1, &blas_framework.device.ocl, NULL, NULL, &err);
  if (err != CL_SUCCESS)
	{
	  printf ("clCreateContext() failed with %d\n", err);
	  return err;
	}

  return CL_SUCCESS;
}

cl_int
hpc_handle_initialize (hpc_handle* blas_handle)
{
  cl_int err;
  cl_command_queue command_queue = clCreateCommandQueue (blas_framework.context.ocl, blas_framework.device.ocl, 0, &err);
  blas_handle->command_queue.ocl = command_queue;
  for (unsigned int i = 0; i < blas_handle->memory_length; ++i) {
	  cl_mem buffer = clCreateBuffer (blas_framework.context.ocl, CL_MEM_READ_WRITE, blas_handle->memory_size[i], NULL, &err);
	  blas_handle->memory[i].ocl = buffer;
  }
  return err;
}

clblasStatus
hpc_blas_initialize (void)
{
  /* Setup clblas. */
  clblasStatus status = clblasSetup ();
  return status;
}

/* Release OpenCL working objects. */
cl_int
hpc_framework_finalize (void)
{
  cl_int err = clReleaseContext (blas_framework.context.ocl);
  return err;
}

/* Release OpenCL working objects. */
cl_int
hpc_handle_finalize (hpc_handle* blas_handle)
{
  cl_int err = clReleaseCommandQueue (blas_handle->command_queue.ocl);
  return err;
}

void
hpc_blas_finalize (void)
{
  /* Finalize work with clblas. */
  clblasTeardown ();
}
