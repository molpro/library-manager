enable_language(CXX)
include(FetchContent)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG "release-1.11.0"
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)


if (EXISTS /opt/intel/oneapi OR EXISTS /opt/intel/mkl)
    unset(ENV{MKLROOT}) # let the defaults do work
endif ()

include(LibraryManagerUtils)

if (APPLE)
#    set(PREFERRED_BLAS Intel10_64lp Apple)
#    set(PREFERRED_BLAS Apple)
#    set(PREFERRED_LAPACK OpenBLAS)
endif ()
# set one of the following manually for further testing
#set(PREFERRED_BLAS Generic)
#set(PREFERRED_BLAS OpenBLAS)
#set(PREFERRED_BLAS Apple)
#set(PREFERRED_BLAS Intel10_64lp)
#set(PREFERRED_BLAS Intel10_64lp_seq)
#set(PREFERRED_BLAS Intel10_64dyn)
#set(PREFERRED_BLAS Intel10_64ilp)
if (NOT PREFERRED_LAPACK AND PREFERRED_BLAS)
    set(PREFERRED_LAPACK ${PREFERRED_BLAS})
endif ()


add_library(libtestblas INTERFACE)
message(STATUS "Preferred BLAS ${PREFERRED_BLAS}")
LibraryManager_BLAS(libtestblas INTERFACE ${PREFERRED_BLAS})
print_target_properties(BLAS::BLAS)
print_variable(MKL)
print_variable(MKL_TYPE)
print_variable(BLA_VENDOR_FOUND)
add_executable(testblas testblas.cpp)
set_property(TARGET testblas PROPERTY CXX_STANDARD 17)
target_compile_definitions(testblas PRIVATE -DBLA_VENDOR="${BLA_VENDOR_FOUND}")
target_link_libraries(testblas PRIVATE libtestblas gmock_main)
gtest_discover_tests(testblas)
add_test(testblas testblas)

add_library(libtestlapack INTERFACE)
message(STATUS "Preferred LAPACK ${PREFERRED_LAPACK}")
LibraryManager_LAPACK(libtestlapack INTERFACE ${PREFERRED_LAPACK})
include(LibraryManagerUtils)
print_target_properties(LAPACK::LAPACK)
print_variable(MKL)
print_variable(MKL_TYPE)
print_variable(BLA_VENDOR_FOUND)
add_executable(testlapack testlapack.cpp)
set_property(TARGET testlapack PROPERTY CXX_STANDARD 17)
target_compile_definitions(testlapack PRIVATE -DBLA_VENDOR="${BLA_VENDOR_FOUND}")
target_link_libraries(testlapack PRIVATE libtestlapack gmock_main)
gtest_discover_tests(testlapack)
add_test(testlapack testlapack)

add_executable(testblaslapack testblaslapack.cpp)
set_property(TARGET testblaslapack PROPERTY CXX_STANDARD 17)
target_compile_definitions(testblaslapack PRIVATE -DBLA_VENDOR="${BLA_VENDOR_FOUND}")
target_link_libraries(testblaslapack PRIVATE BLAS::BLAS LAPACK::LAPACK gmock_main)
gtest_discover_tests(testblaslapack)
add_test(testblaslapack testblaslapack)

find_package(Eigen3 3.3 NO_MODULE)
if (TARGET Eigen3::Eigen)
    print_target_properties(Eigen3::Eigen)
    add_executable(testeigen testeigen.cpp)
    set_property(TARGET testeigen PROPERTY CXX_STANDARD 17)
    target_compile_definitions(testeigen PRIVATE -DBLA_VENDOR="${BLA_VENDOR_FOUND}")
    target_link_libraries(testeigen PUBLIC
            BLAS::BLAS
            LAPACK::LAPACK
            Eigen3::Eigen
            gmock_main)
    gtest_discover_tests(testeigen)
    add_test(testeigen testeigen)
endif ()