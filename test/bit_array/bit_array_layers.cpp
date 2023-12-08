
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <mgtl/bit_array/bit_size.hpp>
#include <mgtl/bit_array/details/bit_array_different_size.hpp>
#include <mgtl/bit_array/details/bit_array_layer.hpp>


using namespace mgtl::bit_array;

using mgtl::bit_array::bite_size::size_type;

#define TEST_TYPES                                                                              \
  (details::BitArrayWithLayers_t<100, uint8_t>), (details::BitArrayWithLayers_t<500, uint8_t>), \
    (details::BitArrayWithLayers_t<815, uint8_t>), (details::BitArrayWithLayers_t<4412, uint8_t>), \
  (details::BitArrayWithLayers_t<100, uint16_t>), (details::BitArrayWithLayers_t<500, uint16_t>), \
    (details::BitArrayWithLayers_t<815, uint16_t>), (details::BitArrayWithLayers_t<4412, uint16_t>), \
  (details::BitArrayWithLayers_t<100, uint32_t>), (details::BitArrayWithLayers_t<500, uint32_t>), \
    (details::BitArrayWithLayers_t<815, uint32_t>), (details::BitArrayWithLayers_t<4412, uint32_t>)

TEMPLATE_TEST_CASE("BitArrayLayers set untill full", "[tag]", TEST_TYPES)// NOLINT
{
  using BitArrayT = TestType;
  BitArrayT test_bit_array;
  for (size_type i = 0; i < BitArrayT::size(); i++) {
    test_bit_array.set(i);
    REQUIRE(test_bit_array.get(i) == true);// NOLINT
    REQUIRE(test_bit_array[i] == true);// NOLINT
    REQUIRE(test_bit_array.popcount() == static_cast<size_type>(i + 1));// NOLINT
  }
}
