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

#define MAX_PLATFORM_COUNT 8
#define PLATFORM_ATTRIBUTE_COUNT 3

cl_uint platform_count;
cl_platform_id *platforms;

const cl_platform_info attribute_types[PLATFORM_ATTRIBUTE_COUNT] =
  { CL_PLATFORM_NAME, CL_PLATFORM_VENDOR, CL_PLATFORM_VERSION };

hpc_framework_initialize (void)
{
  cl_int err = CL_SUCCESS;
  uint8_t i, j;
  char* info;
  size_t info_size;
  // get platform count
  clGetPlatformIDs (MAX_PLATFORM_COUNT, NULL, &platform_count);

  // get all platforms
  platforms = (cl_platform_id*) malloc (sizeof(cl_platform_id) * platform_count);
  clGetPlatformIDs (platform_count, platforms, NULL);

  // for each platform print all attributes
  for (i = 0; i < platform_count; i++)
	{
	  printf ("\n Platform[%d]: ", i + 1);
	  for (j = 0; j < PLATFORM_ATTRIBUTE_COUNT; j++)
		{
		  // get platform attribute value size
		  clGetPlatformInfo (platforms[i], attribute_types[j], 0, NULL, &info_size);
		  info = (char*) malloc (info_size);
		  // get platform attribute value
		  clGetPlatformInfo (platforms[i], attribute_types[j], info_size, info, NULL);
		  printf ("| %s ", info);
		  free (info);
		}
	  printf ("\n");
	}
  free (platforms);

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

  blas_framework.context.ocl = clCreateContext (NULL, 1, &blas_framework.device.ocl, NULL, NULL, &err);
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
  cl_int err = CL_SUCCESS;
  cl_command_queue command_queue = clCreateCommandQueue (blas_framework.context.ocl, blas_framework.device.ocl, 0,
														 &err);
  if (err != CL_SUCCESS)
	{
	  printf ("clCreateCommandQueue() failed with %d\n", err);
	  return err;
	}
  blas_handle->command_queue.ocl = command_queue;
  for (uint8_t i = 0; i < blas_handle->memory_length; ++i)
	{
	  cl_mem buffer = clCreateBuffer (blas_framework.context.ocl, CL_MEM_READ_WRITE, blas_handle->memory_size[i], NULL,
									  &err);
	  if (err != CL_SUCCESS)
		{
		  printf ("clCreateBuffer() failed with %d\n", err);
		  return err;
		}
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
  for (uint8_t i = 0; i < blas_handle->memory_length; ++i)
	{
	  /* Release OpenCL memory objects. */
	  err = clReleaseMemObject (blas_handle->memory[i].ocl);
	  if (err != CL_SUCCESS)
		{
		  printf ("clReleaseMemObject() failed with %d\n", err);
		  return err;
		}
	}
  return err;
}

void
hpc_blas_finalize (void)
{
  /* Finalize work with clblas. */
  clblasTeardown ();
}
