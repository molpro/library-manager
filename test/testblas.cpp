#include "cblas.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#ifndef HAVE_CBLAS
#error HAVE_CBLAS should be defined
#endif
using ::testing::HasSubstr;

TEST(LibraryManager, blas) {
  std::cout << "Test BLAS with BLAS/LAPACK library " << BLA_VENDOR << std::endl;
#ifdef HAVE_MKL
  EXPECT_THAT(BLA_VENDOR,::testing::HasSubstr("Intel10_"));
#else
  EXPECT_THAT(BLA_VENDOR,::testing::Not(::testing::HasSubstr("Intel10_")));
#endif
  std::vector<double> a(3, 1), b(3, 1);
  EXPECT_EQ(cblas_ddot(a.size(), a.data(), 1, a.data(), 1), a.size());
}