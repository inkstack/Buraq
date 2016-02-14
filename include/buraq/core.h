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
#pragma once

#if defined(__APPLE__) || defined(__MACOSX)
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif


#include "buraq/api.h"

#include "buraq/types.h"

#ifdef __DEBUG__
#define DEBUG(format,...) printf("File: "__FILE__", Line: %05d: "format"\n", __LINE__, ##__VA_ARGS__)
#else
#define DEBUG(format,...)
#endif

union hpc_platofrm {
  cl_platform_id ocl;
};

union hpc_device {
  cl_device_id ocl;
};

union hpc_context {
  cl_context ocl;
};

union hpc_command_queue {
  cl_command_queue ocl;
};

union hpc_memory {
  cl_mem ocl;
};

union hpc_event {
  cl_event ocl;
};


typedef struct _hpc_framework {
  union hpc_platofrm platform;
  union hpc_device device;
  union hpc_context context;
} hpc_framework;

typedef struct _hpc_handle {
  union hpc_command_queue command_queue;
  union hpc_memory* memory;
  int* memory_size;
  unsigned int memory_length;
  union hpc_event event;
} hpc_handle;

/**
*  @brief
*    Print information about the library to the console
*/
BURAQ_API int print_info();

BURAQ_API void print_result_s1 (size_t N, cl_float X[], cl_float Y[]);
