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
  hpc_swap (void);
}


TEST_F(swap_test, CheckSomeResults)
  {
	EXPECT_EQ((unsigned int) 0, hpc_swap());
  }
