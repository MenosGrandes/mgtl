#include <mgtl/bit_array/bit_array.hpp>
#include <catch2/catch_test_macros.hpp>



TEST_CASE("BitArray set test", "[manipulator]")
{

    SECTION( "64 - same size" ) {
    using BitArray = BitArray<64,uint64_t>;
    BitArray ba;
    for(BitArray::memory_t i = 0; i < ba.number_of_bites_v;i++)
    {
        REQUIRE(ba.get(i) == false);
        ba.set(i);
        REQUIRE(ba.get(i) == true);
        ba.clear(i);
        REQUIRE(ba.get(i) == false);

    }
    }

    SECTION( "32 - same size" ) {
    using BitArray = BitArray<32,uint32_t>;
    BitArray ba;
    for(BitArray::memory_t i = 0; i < ba.number_of_bites_v;i++)
    {
        REQUIRE(ba.get(i) == false);
        ba.set(i);
        REQUIRE(ba.get(i) == true);
        ba.clear(i);
        REQUIRE(ba.get(i) == false);

    }
    }
    SECTION( "16- same size" ) {
    using BitArray = BitArray<16,uint16_t>;
    BitArray ba;
    for(BitArray::memory_t i = 0; i < ba.number_of_bites_v;i++)
    {
        REQUIRE(ba.get(i) == false);
        ba.set(i);
        REQUIRE(ba.get(i) == true);
        ba.clear(i);
        REQUIRE(ba.get(i) == false);

    }
    }
    SECTION( "8- same size" ) {
    using BitArray = BitArray<8,uint8_t>;
    BitArray ba;
    for(BitArray::memory_t i = 0; i < ba.number_of_bites_v;i++)
    {
        REQUIRE(ba.get(i) == false);
        ba.set(i);
        REQUIRE(ba.get(i) == true);
        ba.clear(i);
        REQUIRE(ba.get(i) == false);

    }
    }

}
