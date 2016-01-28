#include <stdio.h>
#include <stdlib.h>

#include "buraq/version.h"
#include "buraq/core.h"

int
print_info (void)
{
  puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
  int x;
  for (x = 0; x < 1000; x++)
	{
	  float z = (x / (float) 1000 * 2);
	  printf ("%f\n", z);
	}
  return EXIT_SUCCESS;
}
