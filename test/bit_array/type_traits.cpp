#include <catch2/catch_test_macros.hpp>
#include <mgtl/bit_array/constants.hpp>
#include <mgtl/type_traits/type_traits.hpp>

using namespace mgtl::type_traits;
using namespace mgtl::bit_array::constants;


TEST_CASE("is_one_of_v", "[tag]")
{
  STATIC_REQUIRE(is_one_of_v<_16_t, _16_t> == is_true_v);
  STATIC_REQUIRE(is_one_of_v<_16_t, _16_t, _32_t> == is_true_v);
  STATIC_REQUIRE(is_one_of_v<_16_t, _16_t, _32_t, _64_t> == is_true_v);
  STATIC_REQUIRE(is_one_of_v<_16_t, _16_t, _32_t, _64_t, _8_t> == is_true_v);
  STATIC_REQUIRE(is_one_of_v<i_const_t<_8>, _16_t, _32_t, _64_t, _8_t> == is_true_v);
  STATIC_REQUIRE_FALSE(is_one_of_v<i_const_t<9>, _16_t, _32_t, _64_t, _8_t> == is_true_v);
}
