#include <mgtl/bit_array/details/bit_array_different_size.hpp>
#include <mgtl/bit_array/details/bit_array_same_size.hpp>
#pragma once

using namespace mgtl::bit_array::details;
namespace mgtl::bit_array::printer {

template<std::size_t NUMBER_OF_BITS, typename _memory_t>
std::ostream &operator<<(std::ostream &os, const _BitArrayBase_SameSize_t<NUMBER_OF_BITS, _memory_t> &L)
{
  os << "[ " << L._data << " ]\n";

  return os;
}
template<std::size_t NUMBER_OF_BITS, typename _memory_t>
std::ostream &operator<<(std::ostream &os, const _BitArrayDifferentSize_t<NUMBER_OF_BITS, _memory_t> &L)
{
  os << "[ ";
  for (auto it : L._data) { os << it << " "; }
  os << "]\n";
  return os;
}

struct PrintAsBytes
{
  template<std::size_t NUMBER_OF_BITS, typename _memory_t>
  static std::string print(const _BitArrayDifferentSize_t<NUMBER_OF_BITS, _memory_t> &l)
  {
    using bite_array_t = _BitArrayDifferentSize_t<NUMBER_OF_BITS, _memory_t>;
    using bite_array_t::base_1::BitManipulatorImp::_1;

    std::string s;

    size_t counter = 0;
    for (auto whole = 0; whole < bite_array_t::memory_size_whole_v; whole++) {
      for (auto digit = 0; digit < bite_array_t::memory_t_digits; digit++) {
        const char _char = (((l._data[whole] >> counter) & _1) ? '1' : '0');
        s += _char;
        counter++;
      }
    }

    for (auto rest = 0; rest < bite_array_t::memory_size_rest_v; rest++) {
      const char _char = (((l._data[bite_array_t::memory_size_whole_v] >> counter) & _1) ? '1' : '0');
      s += _char;
      counter++;
    }
    return s;
  }

  template<std::size_t NUMBER_OF_BITS, typename _memory_t>
  static std::string print(const _BitArrayBase_SameSize_t<NUMBER_OF_BITS, _memory_t> &l)
  {

    using bite_array_t = _BitArrayDifferentSize_t<NUMBER_OF_BITS, _memory_t>;
    using bite_array_t::base_1::BitManipulatorImp::_1;
    std::string s;
    for (auto c = 0; c < NUMBER_OF_BITS; c++) {
      const char _char = (((l._data >> c) & _1) ? '1' : '0');
      s += _char;
    }
    return s;
  }
};
}// namespace mgtl::bit_array::printer
