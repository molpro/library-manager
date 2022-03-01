#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "molpro/lapacke.h"
#include <vector>
using ::testing::HasSubstr;

lapack_int thing;
TEST(LibraryManager, lapacke) {
#ifndef HAVE_LAPACKE
#error "Missing lapacke support"
#endif
  std::cout << "Test Lapack with BLAS/LAPACK library " << BLA_VENDOR << std::endl;
  double a[5][3] = {1, 1, 1, 2, 3, 4, 3, 5, 2, 4, 2, 5, 5, 4, 3};
  double b[5][2] = {-10, -3, 12, 14, 14, 12, 16, 16, 18, 16};
  lapack_int info = LAPACKE_dgels(LAPACK_ROW_MAJOR, 'N', 5, 3, 2, *a, 3, *b, 2);
  EXPECT_EQ(info, 0);
}
