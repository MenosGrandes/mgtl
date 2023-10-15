#include <catch2/catch_test_macros.hpp>

#include <mgtl/bit_array/bit_array.hpp>




TEST_CASE("is_same_bite_size_v constexpr test", "[tag]")
{
STATIC_REQUIRE(is_integer_but_not_zero_v<0> == is_false_v);
STATIC_REQUIRE(is_integer_but_not_zero_v<1> == is_true_v);

STATIC_REQUIRE(is_same_bite_size_v<8, uint8_t> == is_true_v);
STATIC_REQUIRE(is_same_bite_size_v<16, uint16_t> == is_true_v);
STATIC_REQUIRE(is_same_bite_size_v<32, uint32_t> == is_true_v);
STATIC_REQUIRE(is_same_bite_size_v<64, uint64_t> == is_true_v);
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
    STATIC_REQUIRE(std::is_same_v<BitArray64, BitArray<64, uint64_t>>);
    STATIC_REQUIRE(std::is_same_v<BitArray32, BitArray<32, uint32_t>>);
    STATIC_REQUIRE(std::is_same_v<BitArray16, BitArray<16, uint16_t>>);
    STATIC_REQUIRE(std::is_same_v<BitArray8, BitArray<8, uint8_t>>);



    STATIC_REQUIRE(is_not_same_v<BitArray64, BitArray<32, uint32_t>>);
    STATIC_REQUIRE(is_not_same_v<BitArray64, BitArray<8, uint8_t>>);
    STATIC_REQUIRE(is_not_same_v<BitArray64, BitArray<16, uint16_t>>);

    STATIC_REQUIRE(is_not_same_v<BitArray32, BitArray<64, uint64_t>>);
    STATIC_REQUIRE(is_not_same_v<BitArray32, BitArray<8, uint8_t>>);
    STATIC_REQUIRE(is_not_same_v<BitArray32, BitArray<16, uint16_t>>);

    STATIC_REQUIRE(is_not_same_v<BitArray16, BitArray<64, uint64_t>>);
    STATIC_REQUIRE(is_not_same_v<BitArray16, BitArray<8, uint8_t>>);
    STATIC_REQUIRE(is_not_same_v<BitArray16, BitArray<32, uint32_t>>);

    STATIC_REQUIRE(is_not_same_v<BitArray8, BitArray<64, uint64_t>>);
    STATIC_REQUIRE(is_not_same_v<BitArray8, BitArray<16, uint16_t>>);
    STATIC_REQUIRE(is_not_same_v<BitArray8, BitArray<32, uint32_t>>);

}
