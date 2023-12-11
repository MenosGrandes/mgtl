

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>//NOLINT
#include <cstdint>
#include <iostream>//NOLINT
#include <mgtl/bit_array/bit_array.hpp>
#include <mgtl/bit_array/bit_size.hpp>
#include <mgtl/bit_array/details/bit_array_different_size.hpp>
#include <mgtl/bit_array/details/bit_array_layer.hpp>
#include <mgtl/bit_array/details/bit_array_same_size.hpp>
#include <mgtl/bit_array/printer.hpp>//NOLINT
#include <array>

using namespace mgtl::bit_array;

using mgtl::bit_array::bite_size::size_type;

#define TEST_TYPES                                                                   \
  (BitArray<8, uint8_t>), (BitArray_t<8>), (_BitArrayBase_SameSize_t<16, uint16_t>), \
    (_BitArrayDifferentSize_t<9, uint8_t>), (BitArrayWithLayers_t<65, uint8_t>)

TEMPLATE_TEST_CASE("Printer test", "[tag]", TEST_TYPES)// NOLINT
{
  using BitArrayT = TestType;
  BitArrayT test_bit_array;

  const auto indices = std::array<size_type, 6>{ 0, 1, 2, 5, 8, 11 };
  for (auto value : indices) { test_bit_array.set(value); }
  std::cout << mgtl::bit_array::printer::PrintAsBytes::print(test_bit_array) << "\n";

}
