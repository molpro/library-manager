#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "molpro/lapacke.h"
#include "molpro/cblas.h"
#include <vector>
#include <chrono>

lapack_int thing;

TEST(LibraryManager, blas_and_lapack) {
#ifndef HAVE_LAPACKE
#error "Missing lapacke support"
#endif
#ifndef HAVE_CBLAS
#error "Missing cblas support"
#endif

  std::cout << "Test BLAS and Lapack with BLAS/LAPACK library " << BLA_VENDOR << std::endl;
  double a[5][3] = {1, 1, 1, 2, 3, 4, 3, 5, 2, 4, 2, 5, 5, 4, 3};
  double b[5][2] = {-10, -3, 12, 14, 14, 12, 16, 16, 18, 16};
  lapack_int info = LAPACKE_dgels(LAPACK_ROW_MAJOR, 'N', 5, 3, 2, *a, 3, *b, 2);
  EXPECT_EQ(info, 0);

  std::vector<double> va(3, 1);
  EXPECT_EQ(cblas_ddot(va.size(), va.data(), 1, va.data(), 1), va.size());
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
