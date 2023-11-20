
#include <catch2/catch_test_macros.hpp>
#include <mgtl/bit_array/type_traits.hpp>
#include <mgtl/type_traits/type_traits.hpp>
#include <mgtl/bit_array/constants.hpp>


using namespace mgtl::type_traits;
using namespace mgtl::bit_array::type_traits;


// NOLINTNEXTLINE
TEST_CASE("is_buildin_v", "[tag]")
{
  STATIC_REQUIRE(is_buildin_v<_8> == true_v);
  STATIC_REQUIRE(is_buildin_v<_16> == true_v);
  STATIC_REQUIRE(is_buildin_v<_32> == true_v);
  STATIC_REQUIRE(is_buildin_v<_64> == true_v);
  STATIC_REQUIRE(is_buildin_v<i_const_v<234>> == false_v);
}

// NOLINTNEXTLINE
TEST_CASE("is_buildin_size_v", "[tag]")
{
  STATIC_REQUIRE(is_buildin_size_v<_32> == true_v);
  STATIC_REQUIRE(is_buildin_size_v<_64> == true_v);
  STATIC_REQUIRE(is_buildin_size_v<_8> == true_v);
  STATIC_REQUIRE(is_buildin_size_v<_16> == true_v);
}

// NOLINTNEXTLINE
TEST_CASE("is_less_v", "[tag]")
{
  STATIC_REQUIRE(is_less_v<_32_t, _16_t> == false_v);
  STATIC_REQUIRE(is_less_v<_16_t, _32_t> == true_v);
}
