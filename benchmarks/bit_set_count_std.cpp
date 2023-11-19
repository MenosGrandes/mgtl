#include <bitset>
#include <nanobench.h>

#include <cstddef>
int main()
{

  ankerl::nanobench::Bench().run("bitmap - popcount", [&] {
    constexpr auto BIT_SET_SIZE {64};
    std::bitset<BIT_SET_SIZE> bit_array_test;
    for (size_t i = 0; i < BIT_SET_SIZE; i++) {
      bit_array_test = bit_array_test.set(i,true);
      auto count = bit_array_test.count();
      ankerl::nanobench::doNotOptimizeAway(count);
    }
  });
}
