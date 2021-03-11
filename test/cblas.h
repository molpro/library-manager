#ifndef MOLPRO_DEPENDENCIES_UTILITIES_SRC_MOLPRO_CBLAS_H_
#define MOLPRO_DEPENDENCIES_UTILITIES_SRC_MOLPRO_CBLAS_H_

/*!
 * @brief Non-forcing inclusion of cblas header file.
 * If successful, HAVE_CBLAS is defined.
 */
#if __has_include(<mkl_lapacke.h>) && ! defined(NO_USE_MKL)
#include <mkl_cblas.h>
#define HAVE_CBLAS
#define HAVE_MKL
#elif __has_include(<Accelerate/Accelerate.h>) && ! defined(NO_USE_ACCELERATE)
#include <Accelerate/Accelerate.h>
#define HAVE_CBLAS
#define HAVE_ACCELERATE
#elif __has_include(<cblas.h>)
#include <cblas.h>
#define HAVE_CBLAS
#endif

#endif //MOLPRO_DEPENDENCIES_UTILITIES_SRC_MOLPRO_CBLAS_H_
