#include <stdint.h>
#include <catch2/catch_test_macros.hpp>
#include <mgtl/bit_array/bit_array.hpp>
#include <mgtl/bit_array/details/bit_array_same_size.hpp>
#include <mgtl/bit_array/constants.hpp>

using namespace mgtl::bit_array;

#include <catch2/catch_template_test_macros.hpp>

#define TEST_TYPES                                                                                           \
  BitArray64_t, BitArray32_t, BitArray16_t, BitArray8_t, (BitArray<64, uint64_t>), (BitArray<32, uint32_t>), \
    (BitArray<16, uint16_t>), (BitArray<8, uint8_t>), (BitArray<12, uint8_t>), (BitArray<441, uint64_t>),    \
    (BitArray<223, uint8_t>)

TEMPLATE_TEST_CASE("BitArray set test", "[tag]", TEST_TYPES)
{

  using BitArrayT = TestType;
  BitArrayT test_bit_array;
  for (typename BitArrayT::base::memory_t i = 0; i < BitArrayT::size(); i++) {
    REQUIRE(test_bit_array.get(i) == false);
    test_bit_array.set(i);
    REQUIRE(test_bit_array.get(i) == true);
    test_bit_array.clear(i);
    REQUIRE(test_bit_array.get(i) == false);
  }
}

TEST_CASE("BitArray popcount" , "[tag]")
{
  BitArray8_t bitArray;
  REQUIRE(bitArray.popcount() == 0);
}
