
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp> //NOLINT
#include <cstdint>
#include <iostream> //NOLINT
#include <mgtl/bit_array/bit_size.hpp>
#include <mgtl/bit_array/details/bit_array_layer.hpp>
#include <mgtl/bit_array/printer.hpp>//NOLINT


using namespace mgtl::bit_array;

using mgtl::bit_array::bite_size::size_type;

#define TEST_TYPES (details::BitArrayWithLayers_t<64, uint8_t>)

TEMPLATE_TEST_CASE("BitArrayLayers set untill full", "[tag]", TEST_TYPES)// NOLINT
{
  using BitArrayT = TestType;
  BitArrayT test_bit_array;

  test_bit_array.set(0);
  mgtl::bit_array::printer::PrintAsBytes::print(test_bit_array);
}
