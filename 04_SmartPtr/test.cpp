#include "../test_runner.h"
#include "smart_ptr.h"

void Test_constructors() {
  {
    UniquePtr<bool> u_ptr;
    ASSERT(!u_ptr.Get());

    SharedPtr<bool> s_ptr;
    ASSERT(!s_ptr.Get());
  }
  {
    UniquePtr u_ptr(new int(5));
    ASSERT(u_ptr.Get());
    ASSERT_EQUAL(*u_ptr, 5);

    SharedPtr s_ptr(new int(5));
    ASSERT(s_ptr.Get());
    ASSERT_EQUAL(*s_ptr, 5);
  }
  {
    UniquePtr u_ptr(new int(5));
    UniquePtr u_ptr_m(std::move(u_ptr));
    ASSERT(!u_ptr.Get());
    ASSERT(u_ptr_m.Get());
    ASSERT_EQUAL(*u_ptr_m, 5);
    
    SharedPtr s_ptr(new int(5));
    SharedPtr s_ptr_c(s_ptr);
    ASSERT(s_ptr.Get());
    ASSERT_EQUAL(*s_ptr, 5);
    ASSERT(s_ptr_c.Get());
    ASSERT_EQUAL(*s_ptr_c, 5);
    SharedPtr s_ptr_m(std::move(s_ptr));
    ASSERT(!s_ptr.Get());
    ASSERT(s_ptr_m.Get());
    ASSERT_EQUAL(*s_ptr_m, 5);
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, Test_constructors);
  /* Tests */
  return 0;
}
