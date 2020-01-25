#include "../test_runner.h"
#include "fraction.h"

void Test_addition() {
  for (int i = -99; i < 100; ++i)
    for (int j = -99; j < 100; ++j)
      ASSERT_EQUAL(Fraction(i) + Fraction(j), Fraction(i + j));
  for (int i = -99; i < 100; ++i)
    for (int j = -99; j < 100; ++j) {
      Fraction x(i);
      x += Fraction(j);
      ASSERT_EQUAL(x, Fraction(i + j));
    }

  for (int n1 = -99; n1 < 100; ++n1)
    for (int d1 = 1; d1 < 100; ++d1)
      for (int n2 = -99; n2 < 100; ++n2)
        for (int d2 = 1; d2 < 100; ++d2) {
          Fraction x(n1, d1);
          Fraction y(n2, d2);
          ASSERT_EQUAL(x + y, Fraction(n1 * d2 + n2 * d1, d1 * d2));
        }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, Test_addition);
  /* Tests */
  return 0;
}
