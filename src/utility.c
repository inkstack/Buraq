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
#include <stdio.h>
#include <stdlib.h>

#include "buraq/version.h"
#include "buraq/core.h"

int
print_info (void)
{
  puts ("!!!Hello World!!!"); /* prints !!!Hello World!!! */
  int x;
  for (x = 0; x < 1000; x++)
	{
	  float z = (x / (float) 1000 * 2);
	  printf ("%f\n", z);
	}
  return EXIT_SUCCESS;
}

void
print_result_s1 (size_t N, cl_float X[], cl_float Y[])
{
  size_t i;
  printf ("X:\n");
  for (i = 0; i < N; i++)
	{
	  printf ("\t%f\n", X[i]);
	}
  printf ("Y:\n");
  for (i = 0; i < N; i++)
	{
	  printf ("\t%f\n", Y[i]);
	}
}
