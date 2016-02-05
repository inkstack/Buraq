#include <gmock/gmock.h>

extern "C"
{
#include "buraq/pot.h"
}


class gemm_test : public testing::Test
{
public:
};

extern "C"
{
  extern int BURAQ_API
  hpc_blas_gemm (void);
}


TEST_F(gemm_test, CheckSomeResults)
  {
	EXPECT_EQ((unsigned int) 0, hpc_blas_gemm());
  }
