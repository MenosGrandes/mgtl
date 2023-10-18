#include <catch2/catch_test_macros.hpp>

#include <mgtl/bit_array/bit_array.hpp>

using namespace bit_array;
using namespace bit_array::bite_size;

TEST_CASE("is_one_of_v", "[tag]")
{
  STATIC_REQUIRE(is_one_of_v<_16_t, _16_t> == is_true_v);
  STATIC_REQUIRE(is_one_of_v<_16_t, _16_t, _32_t> == is_true_v);
  STATIC_REQUIRE(is_one_of_v<_16_t, _16_t, _32_t, _64_t> == is_true_v);
  STATIC_REQUIRE(is_one_of_v<_16_t, _16_t, _32_t, _64_t, _8_t> == is_true_v);
  STATIC_REQUIRE(is_one_of_v<i_const_t<_8>, _16_t, _32_t, _64_t, _8_t> == is_true_v);
  STATIC_REQUIRE_FALSE(is_one_of_v<i_const_t<9>, _16_t, _32_t, _64_t, _8_t> == is_true_v);
}
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
  STATIC_REQUIRE(bit_array::bite_size::is_buildin_size_v<bit_array::_32> == bit_array::is_true_v);
  STATIC_REQUIRE(bit_array::bite_size::is_buildin_size_v<bit_array::_64> == bit_array::is_true_v);
  STATIC_REQUIRE(bit_array::bite_size::is_buildin_size_v<bit_array::_8> == bit_array::is_true_v);
  STATIC_REQUIRE(bit_array::bite_size::is_buildin_size_v<bit_array::_16> == bit_array::is_true_v);
}


  TEST_CASE("BitArray64 internal values", "[tag]")
  {

    using BitArray = BitArray_t<_64>;
    static constexpr auto _1_v = i_const_v<1>;
    STATIC_REQUIRE(BitArray::memory_t_digits == _64);
    STATIC_REQUIRE(BitArray::memory_size_rest_v == _0_v);
    STATIC_REQUIRE(BitArray::number_of_bites_v == _64);
    STATIC_REQUIRE(BitArray::same_bite_size_v == is_true_v);
    STATIC_REQUIRE(BitArray::memory_size_rounded_up_v == _1_v);
    STATIC_REQUIRE(BitArray::memory_size_whole_v == _1_v);
  }
  TEST_CASE("BitArray64 is_same_v", "[tag]")
  {

    using BitArray = BitArray_t<_64>;
    STATIC_REQUIRE(std::is_same_v<BitArray_t<_64>::memory_t, uint64_t>);
    STATIC_REQUIRE(std::is_same_v<BitArray64_t, BitArray>);
  }
/*

  TEST_CASE("BitArray32", "[tag]")
  {
    using BitArray = BitArray_t<_32>;
    static constexpr auto _1_v = i_const_v<1>;
    STATIC_REQUIRE(BitArray_t<_64>::memory_t_digits == _64);
    STATIC_REQUIRE(std::is_same_v<BitArray_t<_32>::memory_t, uint32_t>);
    STATIC_REQUIRE(std::is_same_v<BitArray32_t, BitArray>);
    STATIC_REQUIRE(BitArray::memory_size_rest_v == _0_v);
    STATIC_REQUIRE(BitArray::number_of_bites_v == _32);
    STATIC_REQUIRE(BitArray::same_bite_size_v == is_true_v);
    STATIC_REQUIRE(BitArray::memory_size_rounded_up_v == _1_v);
    STATIC_REQUIRE(BitArray::memory_size_whole_v == _1_v);
  }

  TEST_CASE("BitArray16", "[tag]")
  {
    using BitArray = BitArray_t<_16>;
    static constexpr auto _1_v = i_const_v<1>;
    STATIC_REQUIRE(BitArray_t<_16>::memory_t_digits == _16);
    STATIC_REQUIRE(std::is_same_v<BitArray_t<_16>::memory_t, uint16_t>);
    STATIC_REQUIRE(std::is_same_v<BitArray16_t, BitArray>);
    STATIC_REQUIRE(BitArray::memory_size_rest_v == _0_v);
    STATIC_REQUIRE(BitArray::number_of_bites_v == _16);
    STATIC_REQUIRE(BitArray::same_bite_size_v == is_true_v);
    STATIC_REQUIRE(BitArray::memory_size_rounded_up_v == _1_v);
    STATIC_REQUIRE(BitArray::memory_size_whole_v == _1_v);
  }
  TEST_CASE("BitArray8", "[tag]")
  {
    using BitArray = BitArray_t<_8>;
    static constexpr auto _1_v = i_const_v<1>;
    STATIC_REQUIRE(BitArray_t<_8>::memory_t_digits == _8);
    STATIC_REQUIRE(std::is_same_v<BitArray_t<_8>::memory_t, uint8_t>);
    STATIC_REQUIRE(std::is_same_v<BitArray8_t, BitArray>);
    STATIC_REQUIRE(BitArray::memory_size_rest_v == _0_v);
    STATIC_REQUIRE(BitArray::number_of_bites_v == _8);
    STATIC_REQUIRE(BitArray::same_bite_size_v == is_true_v);
    STATIC_REQUIRE(BitArray::memory_size_rounded_up_v == _1_v);
    STATIC_REQUIRE(BitArray::memory_size_whole_v == _1_v);
  }


TEST_CASE("is_same_bite_size_v constexpr test", "[tag]")
{

  STATIC_REQUIRE(is_integer_but_not_zero_v<0> == is_false_v);
  STATIC_REQUIRE(is_integer_but_not_zero_v<1> == is_true_v);

  STATIC_REQUIRE(is_same_bite_size_v<_8, uint8_t> == is_true_v);
  STATIC_REQUIRE(is_same_bite_size_v<_16, uint16_t> == is_true_v);
  STATIC_REQUIRE(is_same_bite_size_v<_32, uint32_t> == is_true_v);
  STATIC_REQUIRE(is_same_bite_size_v<_64, uint64_t> == is_true_v);
  STATIC_REQUIRE(is_same_bite_size_v<128, uint64_t> == is_false_v);
  STATIC_REQUIRE(is_same_bite_size_v<63, uint64_t> == is_false_v);
  STATIC_REQUIRE(BitArray<128, uint64_t>::memory_t_digits == 64);
  STATIC_REQUIRE(BitArray<127, uint64_t>::memory_t_digits == 64);
  STATIC_REQUIRE(BitArray<128, uint64_t>::memory_size_whole_v == 2);
  STATIC_REQUIRE(BitArray<127, uint64_t>::memory_size_whole_v == 1);

  STATIC_REQUIRE(BitArray<127, uint64_t>::memory_size_rest_v == (127 - 64));
  STATIC_REQUIRE(BitArray<128, uint64_t>::memory_size_rest_v == 0);


  static_assert(is_same_bite_size_v<0, uint8_t> == is_false_v);
  static_assert(is_same_bite_size_v<0, uint16_t> == is_false_v);
  static_assert(is_same_bite_size_v<0, uint32_t> == is_false_v);
  static_assert(is_same_bite_size_v<0, uint64_t> == is_false_v);
}

TEST_CASE("BitArray same size", "[tag]")
{
  STATIC_REQUIRE(std::is_same_v<BitArray64_t, BitArray<_64, uint64_t>>);
  STATIC_REQUIRE(std::is_same_v<BitArray32_t, BitArray<_32, uint32_t>>);
  STATIC_REQUIRE(std::is_same_v<BitArray16_t, BitArray<_16, uint16_t>>);
  STATIC_REQUIRE(std::is_same_v<BitArray8_t, BitArray<_8, uint8_t>>);


  STATIC_REQUIRE(is_not_same_v<BitArray64_t, BitArray<32, uint32_t>>);
  STATIC_REQUIRE(is_not_same_v<BitArray64_t, BitArray<8, uint8_t>>);
  STATIC_REQUIRE(is_not_same_v<BitArray64_t, BitArray<16, uint16_t>>);

  STATIC_REQUIRE(is_not_same_v<BitArray32_t, BitArray<64, uint64_t>>);
  STATIC_REQUIRE(is_not_same_v<BitArray32_t, BitArray<8, uint8_t>>);
  STATIC_REQUIRE(is_not_same_v<BitArray32_t, BitArray<16, uint16_t>>);

  STATIC_REQUIRE(is_not_same_v<BitArray16_t, BitArray<64, uint64_t>>);
  STATIC_REQUIRE(is_not_same_v<BitArray16_t, BitArray<8, uint8_t>>);
  STATIC_REQUIRE(is_not_same_v<BitArray16_t, BitArray<32, uint32_t>>);

  STATIC_REQUIRE(is_not_same_v<BitArray8_t, BitArray<64, uint64_t>>);
  STATIC_REQUIRE(is_not_same_v<BitArray8_t, BitArray<16, uint16_t>>);
  STATIC_REQUIRE(is_not_same_v<BitArray8_t, BitArray<32, uint32_t>>);
}
*/
