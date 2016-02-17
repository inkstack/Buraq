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
hpc_handle* blas_handle;

BURAQ_API int
hpc_blas_swap_s(uint32_t n, hpc_float *X, uint32_t incx, hpc_float *Y, uint32_t incy)
{
  uint32_t X_length = 1 + (n - 1) * abs (incx);
  uint32_t Y_length = 1 + (n - 1) * abs (incy);

  hpc_framework_initialize();
  blas_handle = (hpc_handle *)malloc(sizeof(hpc_handle));
  uint8_t memory_lenght = 2;
  blas_handle->memory_length = memory_lenght;
  hpc_float* parameters[] = {X, Y};
  uint32_t memory_size[] = {X_length * sizeof(cl_float), Y_length * sizeof(cl_float)};
  blas_handle->memory_size = memory_size;
  blas_handle->memory = (hpc_memory *)malloc(memory_lenght * sizeof(hpc_memory));
  hpc_handle_initialize(blas_handle);
  hpc_blas_initialize();
  cl_event event = NULL;
  cl_int err = CL_SUCCESS;

  for (int i = 0; i < memory_lenght; ++i) {
	err = clEnqueueWriteBuffer (blas_handle->command_queue.ocl, blas_handle->memory[i].ocl, CL_TRUE, 0, memory_size[i], parameters[i], 0, NULL, NULL);
  }

  /* Call clblas function. */
  err = clblasSswap (n, blas_handle->memory[0].ocl, 0, incx, blas_handle->memory[1].ocl, 0, incy, 1, &blas_handle->command_queue.ocl, 0, NULL, &event);
  if (err != CL_SUCCESS)
	{
	  printf ("clblasSswap() failed with %d\n", err);
	}
  else
	{
	  /* Wait for calculations to be finished. */
	  err = clWaitForEvents (1, &event);

	  /* Fetch results of calculations from GPU memory. */
	  for (int i = 0; i < memory_lenght; ++i) {
		err = clEnqueueReadBuffer (blas_handle->command_queue.ocl, blas_handle->memory[i].ocl, CL_TRUE, 0, memory_size[i], parameters[i], 0, NULL, NULL);
	  }
	}

  /* Release OpenCL events. */
  clReleaseEvent (event);

  hpc_blas_finalize();
  hpc_handle_finalize(blas_handle);
  hpc_framework_finalize();

  return err;
}

