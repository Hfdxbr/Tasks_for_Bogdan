#include "../test_runner.h"
#include "format.h"

void Test_empty_params() {
  ASSERT_EQUAL(format(""), "");
  ASSERT_EQUAL(format("1"), "1");
  ASSERT_EQUAL(format("very very long string"), "very very long string");
}

void Test_int_params() {
  ASSERT_EQUAL(format("{} + {} = 4", 1, 3), "1 + 3 = 4");
  ASSERT_EQUAL(format("{2} + {1} = 4", 1, 3), "3 + 1 = 4");
  ASSERT_EQUAL(format("{1} / {2} = 0.{2}{2}{2}{2}{2}...", 1, 3), "1 / 3 = 0.33333...");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, Test_empty_params);
  RUN_TEST(tr, Test_int_params);
  /* Tests */
  return 0;
}