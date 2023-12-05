cmake_minimum_required(VERSION 3.15...3.23)

project(CmakeConfigPackageTests LANGUAGES CXX)

# ---- Test as standalone project the exported config package ----

if(PROJECT_IS_TOP_LEVEL OR TEST_INSTALLED_VERSION)
  enable_testing()

  find_package(mgtl CONFIG REQUIRED)#  project_options, ...

  if(NOT TARGET mgtl_options)
    message(FATAL_ERROR "Requiered config package not found!")
    return() # be strictly paranoid for Template Janitor github action! CK
  endif()
endif()

# ---- Dependencies ----
include(${CMAKE_SOURCE_DIR}/cmake_base/benchmark.cmake)
AddBenchmark(bit_array_t_popcount SOURCES bit_array_t_popcount.cpp)
AddBenchmark(bit_set_count_std SOURCES bit_set_count_std.cpp)
AddBenchmark(compare_bit_array_different_size_same_size SOURCES bit_array_t_popcount_diffrent_size_same_size.cpp)
