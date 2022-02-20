#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "lapacke.h"
#include "cblas.h"
#include <vector>

TEST(LibraryManager, blas_and_lapack) {

  std::cout << "Test BLAS and Lapack with BLAS/LAPACK library " << BLA_VENDOR << std::endl;
  double a[5][3] = {1, 1, 1, 2, 3, 4, 3, 5, 2, 4, 2, 5, 5, 4, 3};
  double b[5][2] = {-10, -3, 12, 14, 14, 12, 16, 16, 18, 16};
  lapack_int info = LAPACKE_dgels(LAPACK_ROW_MAJOR, 'N', 5, 3, 2, *a, 3, *b, 2);
  EXPECT_EQ(info, 0);

  std::vector<double> va(3, 1);
  EXPECT_EQ(cblas_ddot(va.size(), va.data(), 1, va.data(), 1), va.size());
}
