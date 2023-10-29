#include <bitset>
#include <nanobench.h>

int main()
{

  ankerl::nanobench::Bench().run("bitmap - popcount", [&] {
    std::bitset<100> bs;
    for (size_t i = 0; i < 100; i++) {
      bs = bs.set(i,true);
      auto c = bs.count();
      ankerl::nanobench::doNotOptimizeAway(c);
    }
  });
}
