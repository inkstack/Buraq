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
 * swap.c
 *
 *  Created on: 2016-2-1
 *      Author: Halo9Pan
 */

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <clBLAS.h>

#include "buraq/pot.h"
#include "_init.h"

hpc_framework blas_framework;
hpc_handle blas_handle;

/* This example uses predefined matrices and their characteristics for
 * simplicity purpose.
 */
static const size_t N = 7;

static hpc_float X[] =
  { 11, 21, 31, 41, 51, 61, 71, };
static const int incx = 1;

static hpc_float Y[] =
  { 45, 23, 39, 45, 50, 55, 65, };
static const int incy = 1;

BURAQ_API int
//hpc_blas_swap(blas_framework handle, int n, float *x, int incx, float *y, int incy)
hpc_blas_swap (void)
{
  int ret = 0;
  int lenX = 1 + (N - 1) * abs (incx);
  int lenY = 1 + (N - 1) * abs (incy);

  hpc_framework_initialize();
  hpc_handle_initialize(&blas_framework, &blas_handle);
  hpc_blas_initialize();
  cl_mem bufX, bufY;
  cl_event event = NULL;
  cl_int err;
  if (err != CL_SUCCESS)
	{
	  printf ("clCreateCommandQueue() failed with %d\n", err);
	  return err;
	}
  /* Prepare OpenCL memory objects and place vectors inside them. */
  bufX = clCreateBuffer (blas_framework.context.ocl, CL_MEM_READ_WRITE, (lenX * sizeof(cl_float)), NULL, &err);
  bufY = clCreateBuffer (blas_framework.context.ocl, CL_MEM_READ_WRITE, (lenY * sizeof(cl_float)), NULL, &err);

  err = clEnqueueWriteBuffer (blas_handle.command_queue.ocl, bufX, CL_TRUE, 0, (lenX * sizeof(cl_float)), X, 0, NULL, NULL);
  err = clEnqueueWriteBuffer (blas_handle.command_queue.ocl, bufY, CL_TRUE, 0, (lenY * sizeof(cl_float)), Y, 0, NULL, NULL);

  /* Call clblas function. */
  err = clblasSswap (N, bufX, 0, incx, bufY, 0, incy, 1, &blas_handle.command_queue.ocl, 0, NULL, &event);
  if (err != CL_SUCCESS)
	{
	  printf ("clblasSswap() failed with %d\n", err);
	  ret = 1;
	}
  else
	{
	  /* Wait for calculations to be finished. */
	  err = clWaitForEvents (1, &event);

	  /* Fetch results of calculations from GPU memory. */
	  err = clEnqueueReadBuffer (blas_handle.command_queue.ocl, bufX, CL_TRUE, 0, (lenX * sizeof(cl_float)), X, 0, NULL, NULL);
	  err = clEnqueueReadBuffer (blas_handle.command_queue.ocl, bufY, CL_TRUE, 0, (lenY * sizeof(cl_float)), Y, 0, NULL, NULL);

	  /* At this point you will get the result of SSWAP placed in vector X. */
	  print_result_s1 (N, X, Y);
	}

  /* Release OpenCL events. */
  clReleaseEvent (event);

  /* Release OpenCL memory objects. */
  clReleaseMemObject (bufY);
  clReleaseMemObject (bufX);

  hpc_blas_finalize();
  hpc_finalize();

  return ret;
}

