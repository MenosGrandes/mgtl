#include <catch2/catch_test_macros.hpp>
#include <mgtl/bit_array/bit_array.hpp>

using namespace mgtl;
using namespace bit_array;
using namespace bite_size;

template<typename BitArrayT> bool test_bit_array_set_get_clean()
{
  BitArrayT test_bit_array;
  for (typename BitArrayT::base::memory_t i = 0; i < BitArrayT::size(); i++) {
    REQUIRE(test_bit_array.get(i) == false);
    test_bit_array.set(i);
    REQUIRE(test_bit_array.get(i) == true);
    test_bit_array.clear(i);
    REQUIRE(test_bit_array.get(i) == false);
  }

  return true;
}

TEST_CASE("BitArray set test - 64 same size", "[constructor]")
{
  using BitArray = BitArray64_t;
  REQUIRE(test_bit_array_set_get_clean<BitArray>());
}
TEST_CASE("BitArray set test - 64 same size, deducted type", "[constructor]")
{

  using BitArray = BitArray_t<_64>;
  REQUIRE(test_bit_array_set_get_clean<BitArray>());
}
TEST_CASE("BitArray set test - 32 same size", "[constructor]")
{
  using BitArray = BitArray32_t;
  REQUIRE(test_bit_array_set_get_clean<BitArray>());
}


TEST_CASE("BitArray set test - 32 same size, deducted size", "[constructor]")
{

  using BitArray = BitArray_t<_32>;
  REQUIRE(test_bit_array_set_get_clean<BitArray>());
}

TEST_CASE("BitArray set test - 16 same size", "[constructor]")
{

  using BitArray = BitArray16_t;
  REQUIRE(test_bit_array_set_get_clean<BitArray>());
}

TEST_CASE("BitArray set test - 16 same size, deducted size", "[constructor]")
{

  using BitArray = BitArray_t<_16>;
  REQUIRE(test_bit_array_set_get_clean<BitArray>());
}
