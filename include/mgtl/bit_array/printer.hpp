#include <iostream>
#include <mgtl/bit_array/details/bit_array_different_size.hpp>
#include <mgtl/bit_array/details/bit_array_layer.hpp>
#include <mgtl/bit_array/details/bit_array_same_size.hpp>
#pragma once

using namespace mgtl::bit_array::details;

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
template<std::size_t NUMBER_OF_BITS, typename _memory_t>
std::ostream &operator<<(std::ostream &os, const BitArrayWithLayers_t<NUMBER_OF_BITS, _memory_t> &L)
{
  os << "Layer 0[ ";
  for (auto it : L._layer_0) { os << it << " "; }
  os << "]\n";
  os << "Layer 1 " << L._layer_1 << "\n";
  os << "Layer 2 " << L._layer_2 << "\n";
  os << "Layer 3 " << L._layer_3 << "\n";

  return os;
}

namespace mgtl::bit_array::printer {
struct PrintAsBytes
{
  template<std::size_t NUMBER_OF_BITS, typename _memory_t>
  static std::string print(const _BitArrayDifferentSize_t<NUMBER_OF_BITS, _memory_t> &l)
  {
    using bite_array_t = _BitArrayDifferentSize_t<NUMBER_OF_BITS, _memory_t>;

    std::string s;

    for (size_type whole = 0; whole < bite_array_t::memory_size_whole_v; whole++) {
      for (size_type digit = 0; digit < bite_array_t::memory_t_digits; digit++) {
        char _char = static_cast<bool>((l._data[whole] >> digit) & bite_array_t::BitManipulatorImpl::_1) ? '1' : '0';
        s += _char;
      }
    }
    for (size_type rest = 0; rest < bite_array_t::memory_t_digits; rest++) {

      const char _char =
        static_cast<bool>((l._data[bite_array_t::memory_size_whole_v] >> rest) & bite_array_t::BitManipulatorImpl::_1)
          ? '1'
          : '0';
      s += _char;
    }
    return s;
  }

  template<std::size_t NUMBER_OF_BITS, typename _memory_t>
  static std::string print(const _BitArrayBase_SameSize_t<NUMBER_OF_BITS, _memory_t> &l)
  {

    using bite_array_t = _BitArrayDifferentSize_t<NUMBER_OF_BITS, _memory_t>;
    std::cout << bite_array_t::base_1::memory_t_digits << " memory_size_v \n";
    std::string s;
    for (size_type c = 0; c < bite_array_t::base_1::memory_t_digits; c++) {
      const char _char = (((l._data >> c) & bite_array_t::base_1::BitManipulatorImpl::_1) ? '1' : '0');
      s += _char;
    }
    return s;
  }
};
}// namespace mgtl::bit_array::printer
