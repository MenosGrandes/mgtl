#include <catch2/catch_test_macros.hpp>
#include <mgtl/bit_array/bit_array.hpp>

using namespace bit_array;
using namespace bit_array::bite_size;

TEST_CASE("BitArray set test", "[manipulator]")
{

  SECTION("64 - same size")
  {
    SECTION("with explicit type")
    {
      using BitArray = BitArray64_t;
      BitArray test_bit_array;
      for (BitArray::memory_t i = 0; i < test_bit_array.number_of_bites_v; i++) {
        REQUIRE(test_bit_array.get(i) == false);
        test_bit_array.set(i);
        REQUIRE(test_bit_array.get(i) == true);
        test_bit_array.clear(i);
        REQUIRE(test_bit_array.get(i) == false);
      }
    }
    SECTION("with deducted type")
    {
      using BitArray = BitArray_t<_64>;
      BitArray test_bit_array;
      for (BitArray::memory_t i = 0; i < test_bit_array.number_of_bites_v; i++) {
        REQUIRE(test_bit_array.get(i) == false);
        test_bit_array.set(i);
        REQUIRE(test_bit_array.get(i) == true);
        test_bit_array.clear(i);
        REQUIRE(test_bit_array.get(i) == false);
      }
    }
  }

  SECTION("32 - same size")
  {
    using BitArray = BitArray32_t;
    BitArray test_bit_array;
    for (BitArray::memory_t i = 0; i < test_bit_array.number_of_bites_v; i++) {
      REQUIRE(test_bit_array.get(i) == false);
      test_bit_array.set(i);
      REQUIRE(test_bit_array.get(i) == true);
      test_bit_array.clear(i);
      REQUIRE(test_bit_array.get(i) == false);
    }
  }
  SECTION("16- same size")
  {
    using BitArray = BitArray16_t;
    BitArray test_bit_array;
    for (BitArray::memory_t i = 0; i < test_bit_array.number_of_bites_v; i++) {
      REQUIRE(test_bit_array.get(i) == false);
      test_bit_array.set(i);
      REQUIRE(test_bit_array.get(i) == true);
      test_bit_array.clear(i);
      REQUIRE(test_bit_array.get(i) == false);
    }
  }
  SECTION("8- same size")
  {
    using BitArray = BitArray8_t;
    BitArray test_bit_array;
    for (BitArray::memory_t i = 0; i < test_bit_array.number_of_bites_v; i++) {
      REQUIRE(test_bit_array.get(i) == false);
      test_bit_array.set(i);
      REQUIRE(test_bit_array.get(i) == true);
      test_bit_array.clear(i);
      REQUIRE(test_bit_array.get(i) == false);
    }
  }
}
