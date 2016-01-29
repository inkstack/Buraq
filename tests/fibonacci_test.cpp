#include <gmock/gmock.h>

extern "C"
{
#include "buraq/pot.h"
}


class fibonacci_test : public testing::Test
{
public:
};

extern "C"
{
  extern unsigned int BURAQ_API
  fibonacci (unsigned int i);
}


TEST_F(fibonacci_test, CheckSomeResults)
  {
	EXPECT_EQ((unsigned int) 0, fibonacci(0));
	EXPECT_EQ((unsigned int) 1, fibonacci(1));
	EXPECT_EQ((unsigned int) 1, fibonacci(2));
	EXPECT_EQ((unsigned int)21, fibonacci(8));
  }
