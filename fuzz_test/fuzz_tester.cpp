//#include <fmt/core.h>
#include <iterator>
#include <cstddef>
#include <cstdint>

[[nodiscard]] auto sum_values(const uint8_t *Data, size_t Size)
{
  constexpr auto scale = 1000;

  int value = 0;
  for (std::size_t offset = 0; offset < Size; ++offset) {
    value += static_cast<int>(*std::next(Data, static_cast<long>(offset))) * scale;
  }
  return value;
}

// Fuzzer that attempts to invoke undefined behavior for signed integer overflow
// cppcheck-suppress unusedFunction symbolName=LLVMFuzzerTestOneInput
extern "C" int LLVMFuzzerTestOneInput([[maybe_unused]] const uint8_t *Data, [[maybe_unused]] size_t Size)
{
  //fmt::print("Value sum: {}, len{}\n", sum_values(Data, Size), Size); // NOLINT
  return 0;
}
