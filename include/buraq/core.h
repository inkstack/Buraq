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

typedef union _hpc_platofrm {
  cl_platform_id ocl;
} hpc_platofrm;

typedef union _hpc_device {
  cl_device_id ocl;
} hpc_device;

typedef union _hpc_context {
  cl_context ocl;
} hpc_context;

typedef union _hpc_command_queue {
  cl_command_queue ocl;
} hpc_command_queue;

typedef union _hpc_memory {
  cl_mem ocl;
} hpc_memory;

typedef union _hpc_event {
  cl_event ocl;
} hpc_event;


typedef struct _hpc_framework {
  hpc_platofrm platform;
  hpc_device device;
  hpc_context context;
} hpc_framework;

typedef struct _hpc_handle {
  hpc_command_queue command_queue;
  hpc_memory* memory;
  int* memory_size;
  unsigned int memory_length;
  hpc_event event;
} hpc_handle;

/**
*  @brief
*    Print information about the library to the console
*/
BURAQ_API int print_info();

BURAQ_API void print_result_s1 (size_t N, cl_float X[], cl_float Y[]);
