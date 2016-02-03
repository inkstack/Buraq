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

/* This example uses predefined matrices and their characteristics for
 * simplicity purpose.
 */
static const size_t N = 7;

static cl_float X[] = {
    11,
    21,
    31,
    41,
    51,
    61,
    71,
};
static const int incx = 1;

static cl_float Y[] = {
    45,
    23,
    39,
    45,
    50,
    55,
    65,
};
static const int incy = 1;


BURAQ_API int
hpc_blas_swap(blas_handle handle, int n, float *x, int incx, float *y, int incy)
{
    cl_int err;
    cl_platform_id platform = 0;
    cl_device_id device = 0;
    cl_context_properties props[3] = { CL_CONTEXT_PLATFORM, 0, 0 };
    cl_context ctx = 0;
    cl_command_queue queue = 0;
    cl_mem bufX, bufY;
    cl_event event = NULL;
    int ret = 0;
	int lenX = 1 + (N-1)*abs(incx);
	int lenY = 1 + (N-1)*abs(incy);

    /* Setup OpenCL environment. */
    err = clGetPlatformIDs(1, &platform, NULL);
    if (err != CL_SUCCESS) {
        printf( "clGetPlatformIDs() failed with %d\n", err );
        return 1;
    }

    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    if (err != CL_SUCCESS) {
        printf( "clGetDeviceIDs() failed with %d\n", err );
        return 1;
    }

    props[1] = (cl_context_properties)platform;
    ctx = clCreateContext(props, 1, &device, NULL, NULL, &err);
    if (err != CL_SUCCESS) {
        printf( "clCreateContext() failed with %d\n", err );
        return 1;
    }

    queue = clCreateCommandQueue(ctx, device, 0, &err);
    if (err != CL_SUCCESS) {
        printf( "clCreateCommandQueue() failed with %d\n", err );
        clReleaseContext(ctx);
        return 1;
    }

    /* Setup clblas. */
    err = clblasSetup();
    if (err != CL_SUCCESS) {
        printf("clblasSetup() failed with %d\n", err);
        clReleaseCommandQueue(queue);
        clReleaseContext(ctx);
        return 1;
    }

    /* Prepare OpenCL memory objects and place vectors inside them. */
    bufX = clCreateBuffer(ctx, CL_MEM_READ_WRITE, (lenX*sizeof(cl_float)), NULL, &err);
    bufY = clCreateBuffer(ctx, CL_MEM_READ_WRITE, (lenY*sizeof(cl_float)), NULL, &err);

    err = clEnqueueWriteBuffer(queue, bufX, CL_TRUE, 0, (lenX*sizeof(cl_float)), X, 0, NULL, NULL);
    err = clEnqueueWriteBuffer(queue, bufY, CL_TRUE, 0, (lenY*sizeof(cl_float)), Y, 0, NULL, NULL);

    /* Call clblas function. */
    err = clblasSswap( N, bufX, 0, incx, bufY, 0, incy, 1, &queue, 0, NULL, &event);
    if (err != CL_SUCCESS) {
        printf("clblasSswap() failed with %d\n", err);
        ret = 1;
    }
    else {
        /* Wait for calculations to be finished. */
        err = clWaitForEvents(1, &event);

        /* Fetch results of calculations from GPU memory. */
        err = clEnqueueReadBuffer(queue, bufX, CL_TRUE, 0, (lenX*sizeof(cl_float)),
                                    X, 0, NULL, NULL);
        err = clEnqueueReadBuffer(queue, bufY, CL_TRUE, 0, (lenY*sizeof(cl_float)),
                                    Y, 0, NULL, NULL);

        /* At this point you will get the result of SSWAP placed in vector X. */
        print_result_s1(N, X, Y);
    }

    /* Release OpenCL events. */
    clReleaseEvent(event);

    /* Release OpenCL memory objects. */
    clReleaseMemObject(bufY);
    clReleaseMemObject(bufX);

    /* Finalize work with clblas. */
    clblasTeardown();

    /* Release OpenCL working objects. */
    clReleaseCommandQueue(queue);
    clReleaseContext(ctx);

    return ret;
}

