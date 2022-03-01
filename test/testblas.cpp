#include "molpro/cblas.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>
#ifndef HAVE_CBLAS
#error HAVE_CBLAS should be defined
#endif
#include <chrono>
using ::testing::HasSubstr;

TEST(LibraryManager, blas) {
  std::cout << "Test BLAS with BLAS/LAPACK library " << BLA_VENDOR << std::endl;
#ifdef HAVE_MKL
  EXPECT_THAT(BLA_VENDOR, ::testing::HasSubstr("Intel10_"));
#else
  EXPECT_THAT(BLA_VENDOR, ::testing::Not(::testing::HasSubstr("Intel10_")));
#endif
  std::vector<double> a(3, 1), b(3, 1);
  EXPECT_EQ(cblas_ddot(a.size(), a.data(), 1, a.data(), 1), a.size());
  constexpr size_t n = 1000;
  constexpr size_t repeat = 20;
  std::vector<double> ma(n * n, 1);
  std::vector<double> mb(n * n, 1);
  std::vector<double> mc(n * n, 0);
  auto start = std::chrono::system_clock::now();
  for (size_t rep = 0; rep < repeat; ++rep)
    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1,
                ma.data(), n, mb.data(), n, 1, mc.data(), n);
  auto stop = std::chrono::system_clock::now();
  auto milliseconds =
      std::chrono::duration_cast<std::chrono::milliseconds>(stop - start)
          .count();
  auto gflop = std::pow(double(n), 3) * 2 * repeat * 1e-6 / milliseconds;
  std::cout << "dgemm dimension=" << n << " milliseconds=" << milliseconds
            << " gflop=" << gflop << std::endl;
}