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
#set(BLA_VENDOR OpenBLAS)
#set(BLA_VENDOR Apple)
#set(BLA_VENDOR Intel10_64lp)
#set(BLA_VENDOR Intel10_64lp_seq)
#set(BLA_VENDOR Intel10_64dyn)
#set(BLA_VENDOR Intel10_64ilp)


add_library(libtestblas INTERFACE)
message(STATUS "Preferred BLAS ${BLA_VENDOR}")
LibraryManager_BLAS(libtestblas INTERFACE ${BLA_VENDOR})
print_target_properties(BLAS::BLAS)
print_variable(MKL)
print_variable(MKL_TYPE)
print_variable(BLA_VENDOR_FOUND)
add_executable(testblas testblas.cpp)
set_property(TARGET testblas PROPERTY CXX_STANDARD 17)
target_compile_definitions(testblas PRIVATE -DBLA_VENDOR="${BLA_VENDOR}")
target_link_libraries(testblas PRIVATE libtestblas gmock_main)
gtest_discover_tests(testblas)
add_test(testblas testblas)

add_library(libtestlapack INTERFACE)
message(STATUS "Preferred LAPACK ${BLA_VENDOR}")
LibraryManager_LAPACK(libtestlapack INTERFACE ${BLA_VENDOR})
include(LibraryManagerUtils)
print_target_properties(LAPACK::LAPACK)
print_variable(MKL)
print_variable(MKL_TYPE)
print_variable(BLA_VENDOR_FOUND)
add_executable(testlapack testlapack.cpp)
set_property(TARGET testlapack PROPERTY CXX_STANDARD 17)
target_compile_definitions(testlapack PRIVATE -DBLA_VENDOR="${BLA_VENDOR}")
target_link_libraries(testlapack PRIVATE libtestlapack gmock_main)
gtest_discover_tests(testlapack)
add_test(testlapack testlapack)

find_package(Eigen3 3.3 NO_MODULE)
if (TARGET Eigen3::Eigen)
    print_target_properties(Eigen3::Eigen)
    add_executable(testeigen testeigen.cpp)
    set_property(TARGET testeigen PROPERTY CXX_STANDARD 17)
    target_compile_definitions(testeigen PRIVATE -DBLA_VENDOR="${BLA_VENDOR}")
    #    add_library(libtesteigen INTERFACE)
    #    target_link_libraries(libtesteigen INTERFACE Eigen3:Eigen)
    #    print_target_properties(libtesteigen)
    target_link_libraries(testeigen PRIVATE
            Eigen3:Eigen
            LAPACK::LAPACK BLAS::BLAS
            gmock_main)
    gtest_discover_tests(testeigen)
    add_test(testeigen testeigen)
endif ()