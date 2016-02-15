#include <gmock/gmock.h>

extern "C"
{
#include "buraq/pot.h"
}


class swap_test : public testing::Test
{
public:
};

extern "C"
{
  extern int BURAQ_API
  hpc_blas_swap(uint32_t n, hpc_float *X, uint32_t incx, hpc_float *Y, uint32_t incy);
}

/* This example uses predefined matrices and their characteristics for
 * simplicity purpose.
 */
static const uint32_t N = 7;

hpc_float X[] =
  { 11, 21, 31, 41, 51, 61, 71, };
const int incx = 1;

hpc_float Y[] =
  { 45, 23, 39, 45, 50, 55, 65, };
const int incy = 1;

TEST_F(swap_test, CheckSomeResults)
  {
	EXPECT_EQ((unsigned int) 0, hpc_blas_swap(N, X, incx, Y, incy));
  }
