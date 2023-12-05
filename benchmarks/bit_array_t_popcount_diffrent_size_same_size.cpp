#include <cstdint>
#include <cstdlib>
#include <mgtl/bit_array/bit_array.hpp>
#include <mgtl/bit_array/details/bit_array_different_size.hpp>
#include <nanobench.h>
namespace {

template<std::size_t BITES, typename memory_t>
void run_benchmark_different_size(ankerl::nanobench::Bench *bench, char const *name)
{

  bench->run(name, [&] {
    using BitArray_test = mgtl::bit_array::details::_BitArrayDifferentSize_t<BITES, memory_t>;
    BitArray_test bit_array_test;
    for (typename BitArray_test::memory_t i = 0; i < BitArray_test::base::number_of_bites_v; i++) {
      bit_array_test.set(i);
      auto count = bit_array_test.popcount();
      ankerl::nanobench::doNotOptimizeAway(count);
    }
  });
}
template<std::size_t BITES, typename memory_t>
void run_benchmark_same_size(ankerl::nanobench::Bench *bench, char const *name)
{

  bench->run(name, [&] {
    using BitArray_test = mgtl::bit_array::BitArray<BITES, memory_t>;
    BitArray_test bit_array_test;
    for (typename BitArray_test::memory_t i = 0; i < BitArray_test::base::number_of_bites_v; i++) {
      bit_array_test.set(i);
      auto count = bit_array_test.popcount();
      ankerl::nanobench::doNotOptimizeAway(count);
    }
  });
}
}// namespace

int main()
{
  constexpr auto WARMUP{ 200 };
  {
  constexpr auto SIZE{ 128 };
    ankerl::nanobench::Bench bench_v;
    bench_v.title("BitArray set").unit("128").warmup(WARMUP).relative(true);
    bench_v.performanceCounters(true);

    run_benchmark_different_size<SIZE, uint8_t>(&bench_v, "BitArrayDifferentSize  uint8 set");
    run_benchmark_different_size<SIZE, uint16_t>(&bench_v, "BitArrayDifferentSize  uint16 set");
    run_benchmark_different_size<SIZE, uint32_t>(&bench_v, "BitArrayDifferentSize  uint32 set");
    run_benchmark_different_size<SIZE, uint64_t>(&bench_v, "BitArrayDifferentSize uint64 set");
  }
  {
  constexpr auto SIZE{ 64 };
    ankerl::nanobench::Bench bench_v;
    bench_v.title("BitArray set").unit("64").warmup(WARMUP).relative(true);
    bench_v.performanceCounters(true);

    run_benchmark_different_size<SIZE, uint8_t>(&bench_v, "BitArrayDifferentSize  uint8 set");
    run_benchmark_different_size<SIZE, uint16_t>(&bench_v, "BitArrayDifferentSize  uint16 set");
    run_benchmark_different_size<SIZE, uint32_t>(&bench_v, "BitArrayDifferentSize  uint32 set");
    run_benchmark_same_size<SIZE, uint64_t>(&bench_v, "BitArraySameSize  uint64 set");
  }
  {
  constexpr auto SIZE{  320 };
    ankerl::nanobench::Bench bench_v;
    bench_v.title("BitArray set").unit("320").warmup(WARMUP).relative(true);
    bench_v.performanceCounters(true);

    run_benchmark_different_size<SIZE, uint8_t>(&bench_v, "BitArrayDifferentSize  uint8 set");
    run_benchmark_different_size<SIZE, uint16_t>(&bench_v, "BitArrayDifferentSize  uint16 set");
    run_benchmark_different_size<SIZE, uint32_t>(&bench_v, "BitArrayDifferentSize  uint32 set");
    run_benchmark_different_size<SIZE, uint64_t>(&bench_v, "BitArrayDifferentSize uint64 set");
  }
  {
  constexpr auto SIZE{ 640};
    ankerl::nanobench::Bench bench_v;
    bench_v.title("BitArray set").unit("640").warmup(WARMUP).relative(true);
    bench_v.performanceCounters(true);

    run_benchmark_different_size<SIZE, uint8_t>(&bench_v, "BitArrayDifferentSize  uint8 set");
    run_benchmark_different_size<SIZE, uint16_t>(&bench_v, "BitArrayDifferentSize  uint16 set");
    run_benchmark_different_size<SIZE, uint32_t>(&bench_v, "BitArrayDifferentSize  uint32 set");
    run_benchmark_different_size<SIZE, uint64_t>(&bench_v, "BitArrayDifferentSize uint64 set");
  }
  {
  constexpr auto SIZE{ 960 };
    ankerl::nanobench::Bench bench_v;
    bench_v.title("BitArray set").unit("960").warmup(WARMUP).relative(true);
    bench_v.performanceCounters(true);

    run_benchmark_different_size<SIZE, uint8_t>(&bench_v, "BitArrayDifferentSize  uint8 set");
    run_benchmark_different_size<SIZE, uint16_t>(&bench_v, "BitArrayDifferentSize  uint16 set");
    run_benchmark_different_size<SIZE, uint32_t>(&bench_v, "BitArrayDifferentSize  uint32 set");
    run_benchmark_different_size<SIZE, uint64_t>(&bench_v, "BitArrayDifferentSize uint64 set");
  }
  {
  constexpr auto SIZE{ 1280 };
    ankerl::nanobench::Bench bench_v;
    bench_v.title("BitArray set").unit("1280").warmup(WARMUP).relative(true);
    bench_v.performanceCounters(true);

    run_benchmark_different_size<SIZE, uint8_t>(&bench_v, "BitArrayDifferentSize  uint8 set");
    run_benchmark_different_size<SIZE, uint16_t>(&bench_v, "BitArrayDifferentSize  uint16 set");
    run_benchmark_different_size<SIZE, uint32_t>(&bench_v, "BitArrayDifferentSize  uint32 set");
    run_benchmark_different_size<SIZE, uint64_t>(&bench_v, "BitArrayDifferentSize uint64 set");
  }
  /*
  {
    ankerl::nanobench::Bench bench_v;
    bench_v.title("BitArray set").unit("128").warmup(WARMUP).relative(true);
    bench_v.performanceCounters(true);

    run_benchmark_different_size<SIZE * 2, uint8_t>(&bench_v, "BitArrayDifferentSize  uint8 set");
    run_benchmark_different_size<SIZE * 2, uint16_t>(&bench_v, "BitArrayDifferentSize  uint16 set");
    run_benchmark_different_size<SIZE * 2, uint32_t>(&bench_v, "BitArrayDifferentSize  uint32 set");
    run_benchmark_different_size<SIZE * 2, uint64_t>(&bench_v, "BitArrayDifferentSize  uint32 set");
  }*/

  /*
    ankerl::nanobench::Bench().run("BitArrayDifferentSize 64 uint8 set", [&] {
      using BitArray_test = mgtl::bit_array::details::_BitArrayDifferentSize_t<64>;
      BitArray_test bit_array_test;
      for (BitArray_test::memory_t i = 0; i < BitArray_test::base::number_of_bites_v; i++) {
        bit_array_test.set(i);
        auto count = bit_array_test.popcount();
        ankerl::nanobench::doNotOptimizeAway(count);
      }
    });
    ankerl::nanobench::Bench().run("BitArrayDifferentSize 64 uint16_t set", [&] {
      using BitArray_test = mgtl::bit_array::details::_BitArrayDifferentSize_t<64, uint16_t>;
      BitArray_test bit_array_test;
      for (BitArray_test::memory_t i = 0; i < BitArray_test::base::number_of_bites_v; i++) {
        bit_array_test.set(i);
        auto count = bit_array_test.popcount();
        ankerl::nanobench::doNotOptimizeAway(count);
      }
    });
    ankerl::nanobench::Bench().run("BitArrayDifferentSize 64 uint32 set", [&] {
      using BitArray_test = mgtl::bit_array::details::_BitArrayDifferentSize_t<64, uint32_t>;
      BitArray_test bit_array_test;
      for (BitArray_test::memory_t i = 0; i < BitArray_test::base::number_of_bites_v; i++) {
        bit_array_test.set(i);
        auto count = bit_array_test.popcount();
        ankerl::nanobench::doNotOptimizeAway(count);
      }
    });
    ankerl::nanobench::Bench().run("BitArrayDifferentSize 64 uint64 set", [&] {
      using BitArray_test = mgtl::bit_array::details::_BitArrayDifferentSize_t<64, uint64_t>;
      BitArray_test bit_array_test;
      for (BitArray_test::memory_t i = 0; i < BitArray_test::base::number_of_bites_v; i++) {
        bit_array_test.set(i);
        auto count = bit_array_test.popcount();
        ankerl::nanobench::doNotOptimizeAway(count);
      }
    });
    */
}
