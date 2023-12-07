#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <mgtl/bit_array/bit_array.hpp>
#include <mgtl/bit_array/bit_size.hpp>
#include <mgtl/bit_array/details/bit_array_different_size.hpp>
#include <mgtl/bit_array/details/bit_array_same_size.hpp>


using namespace mgtl::bit_array;

#include <catch2/catch_template_test_macros.hpp>
using mgtl::bit_array::bite_size::size_type;

#define TEST_TYPES                                                                                           \
  BitArray64_t, BitArray32_t, BitArray16_t, BitArray8_t, (BitArray<64, uint64_t>), (BitArray<32, uint32_t>), \
    (BitArray<16, uint16_t>), (BitArray<8, uint8_t>), (BitArray<12, uint8_t>), (BitArray<441, uint64_t>),    \
    (BitArray<223, uint8_t>), (BitArray<960, uint8_t>), (BitArray<320, uint8_t>), (BitArray<64, uint8_t>),   \
    (BitArray<230, uint16_t>), (BitArray<9600, uint32_t>), (BitArray<1320, uint64_t>), (BitArray<6100, uint8_t>)


TEMPLATE_TEST_CASE("BitArray set untill full", "[tag]", TEST_TYPES)// NOLINT
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

TEMPLATE_TEST_CASE("BitArray set test", "[tag]", TEST_TYPES)// NOLINT
{
  using BitArrayT = TestType;
  BitArrayT test_bit_array;
  for (size_type i = 0; i < BitArrayT::size(); i++) {
    REQUIRE(test_bit_array.get(i) == false);// NOLINT
    REQUIRE(test_bit_array[i] == false);// NOLINT
    test_bit_array.set(i);
    REQUIRE(test_bit_array.get(i) == true);// NOLINT
    REQUIRE(test_bit_array[i] == true);// NOLINT
    test_bit_array.clear(i);
    REQUIRE(test_bit_array[i] == false);// NOLINT
  }
}

TEMPLATE_TEST_CASE("BitArray popcount", "[tag]", TEST_TYPES)// NOLINT
{
  using BitArrayT = TestType;
  BitArrayT test_bit_array;
  for (size_type i = 0; i < BitArrayT::size(); i++) {
    test_bit_array.set(i);
    REQUIRE(test_bit_array.popcount() == static_cast<size_type>(i + 1));// NOLINT
  }
}
