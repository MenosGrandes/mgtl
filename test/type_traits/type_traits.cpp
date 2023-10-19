
#include <catch2/catch_test_macros.hpp>
#include <mgtl/type_traits/type_traits.hpp>
#include <mgtl/bit_array/type_traits.hpp>
#pragma once


using namespace mgtl::type_traits;
using namespace mgtl::bit_array::type_traits;


TEST_CASE("is_buildin_v", "[tag]")
{
  STATIC_REQUIRE(is_buildin_v<_8> == is_true_v);
  STATIC_REQUIRE(is_buildin_v<_16> == is_true_v);
  STATIC_REQUIRE(is_buildin_v<_32> == is_true_v);
  STATIC_REQUIRE(is_buildin_v<_64> == is_true_v);
  STATIC_REQUIRE(is_buildin_v<i_const_v<234>> == is_false_v);
}
TEST_CASE("is_buildin_size_v", "[tag]")
{
  STATIC_REQUIRE(is_buildin_size_v<_32> == is_true_v);
  STATIC_REQUIRE(is_buildin_size_v<_64> == is_true_v);
  STATIC_REQUIRE(is_buildin_size_v<_8> == is_true_v);
  STATIC_REQUIRE(is_buildin_size_v<_16> == is_true_v);
}
