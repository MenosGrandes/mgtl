include(${CMAKE_SOURCE_DIR}/cmake_base/tests.cmake)
AddTest(bit_array_tests SOURCES  bit_array.cpp)
AddConstexprTests(bit_array_constexpr_tests SOURCES type_traits.cpp bit_array_details_constexpr.cpp)
