#include <mgtl/bit_array/details/bit_array_different_size.hpp>
#include <mgtl/bit_array/details/bit_array_same_size.hpp>
#pragma once

namespace mgtl::bit_array::printer {

using namespace mgtl::bit_array::details;
template<std::size_t NUMBER_OF_BITS, typename _memory_t>
std::ostream &operator<<(std::ostream &os, const _BitArrayBase_SameSize_t<NUMBER_OF_BITS, _memory_t> &L)
{
  os << "[ " << L._data << " ]\n";

  return os;
}
template<std::size_t NUMBER_OF_BITS, typename _memory_t>
std::ostream &operator<<(std::ostream &os, const _BitArrayBase_Array_t<NUMBER_OF_BITS, _memory_t> &L)
{
  os << "[ ";
  for (auto it : L._data) { os << it << " "; }
  os << "]\n";
  return os;
}

struct PrintAsBytes
{
  template<std::size_t NUMBER_OF_BITS, typename _memory_t>
  static std::string print(const _BitArrayBase_Array_t<NUMBER_OF_BITS, _memory_t> &l)
  {
    using bite_array_t = _BitArrayBase_Array_t<NUMBER_OF_BITS, _memory_t>;
    std::string s;

    size_t counter = 0;
    for (_memory_t whole = 0; whole < bite_array_t::memory_size_whole_v; whole++) {
      for (_memory_t digit = 0; digit < bite_array_t::memory_t_digits; digit++) {
        const char _char = (((l._data[whole] >> counter) & static_cast<_memory_t>(1)) ? '1' : '0');
        s += _char;
        counter++;
      }
    }

    for (_memory_t rest = 0; rest < bite_array_t::memory_size_rest_v; rest++) {
      const char _char =
        (((l._data[bite_array_t::memory_size_whole_v] >> counter) & static_cast<_memory_t>(1)) ? '1' : '0');
      s += _char;
      counter++;
    }
    return s;
  }

  template<std::size_t NUMBER_OF_BITS, typename _memory_t>
  static std::string print(const _BitArrayBase_SameSize_t<NUMBER_OF_BITS, _memory_t> &l)
  {
    std::string s;
    for (std::size_t c = 0; c < NUMBER_OF_BITS; c++) {
      const char _char = (((l._data >> c) & static_cast<_memory_t>(1)) ? '1' : '0');
      s += _char;
    }
    return s;
  }
};
}// namespace mgtl::bit_array::printer
