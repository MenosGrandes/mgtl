#include <mgtl/bit_array/bit_array.hpp>
#include <nanobench.h>


int main()
{
  ankerl::nanobench::Bench().run("BitArray_t - popcount", [&] {
    mgtl::bit_array::BitArray_t<100> bs;
    for (mgtl::bit_array::BitArray_t<100>::memory_t i = 0; i < 100; i++) {
      bs.set(i);
      auto c = bs.popcount();
      ankerl::nanobench::doNotOptimizeAway(c);
    }
  });
}
