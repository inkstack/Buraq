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
 *  Created on: 2016-2-17
 *      Author: Halo9Pan
 */

#include "_init.h"

hpc_framework blas_framework;

int
hpc_framework_initialize (void)
{

}

int
hpc_handle_initialize (hpc_handle* blas_handle)
{
}

cublasStatus_t
hpc_blas_initialize (void)
{
}

int
hpc_framework_finalize (void)
{

}

/* Release OpenCL working objects. */
int
hpc_handle_finalize (hpc_handle* blas_handle)
{
}

void
hpc_blas_finalize (void)
{
}
