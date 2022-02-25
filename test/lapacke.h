#ifndef MOLPRO_DEPENDENCIES_UTILITIES_SRC_MOLPRO_LAPACKE_H_
#define MOLPRO_DEPENDENCIES_UTILITIES_SRC_MOLPRO_LAPACKE_H_

/*!
 * @brief Non-forcing inclusion of lapacke header file.
 * If successful, HAVE_LAPACKE is defined.
 */
#if __has_include(<mkl_lapacke.h>) && ! defined(NO_USE_MKL)
#include <mkl_lapacke.h>
#define HAVE_MKL
#define HAVE_LAPACKE
#elif __has_include(<lapacke.h>)
#if __has_include(<Accelerate/Accelerate.h>) && ! defined(NO_USE_ACCELERATE)
#define __CLAPACK_H
#include <Accelerate/Accelerate.h>
#endif
#include <lapacke.h>
#define HAVE_LAPACKE
#endif

#endif //MOLPRO_DEPENDENCIES_UTILITIES_SRC_MOLPRO_LAPACKE_H_
