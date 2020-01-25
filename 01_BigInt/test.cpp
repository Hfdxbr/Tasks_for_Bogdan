#include "../test_runner.h"
#include "bigint.h"

void Test_addition() {
  for (int i = -99; i < 100; ++i)
    for (int j = -99; j < 100; ++j)
      ASSERT_EQUAL(BigInt(i) + BigInt(j), BigInt(i + j));
  for (int i = -99; i < 100; ++i)
    for (int j = -99; j < 100; ++j) {
      BigInt x(i);
      x += BigInt(j);
      ASSERT_EQUAL(x, BigInt(i + j));
    }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, Test_addition);
  /* Tests */
  return 0;
}
