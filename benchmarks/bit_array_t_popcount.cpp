#include <mgtl/bit_array/bit_array.hpp>
#include <nanobench.h>
int main()
{
  ankerl::nanobench::Bench().run("BitArray_t - popcount", [&] {
    constexpr auto BIT_ARRAY_SIZE{ 100 };
    using BitArray_test = mgtl::bit_array::BitArray_t<BIT_ARRAY_SIZE>;
    BitArray_test bit_array_test;
    for (BitArray_test::memory_t i = 0; i < BIT_ARRAY_SIZE; i++) {
      bit_array_test.set(i);
      auto count = bit_array_test.popcount();
      ankerl::nanobench::doNotOptimizeAway(count);
    }
  });
}
