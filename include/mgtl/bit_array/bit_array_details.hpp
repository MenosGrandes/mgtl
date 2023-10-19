
#include <inttypes.h>

#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <mgtl/bit_array/bit_manipulator.hpp>
#include <mgtl/bit_array/bit_size.hpp>
#include <mgtl/bit_array/type_traits.hpp>
#include <mgtl/type_traits/type_traits.hpp>

#pragma once

namespace mgtl {
using namespace mgtl::type_traits;
using namespace mgtl::bit_array;

namespace base {
  template<std::size_t N, typename memory_t> struct _BitArrayBase_t : public bite_size::bite_size<N, memory_t>
  {
    using bite_size_base = bite_size::bite_size<N, memory_t>;
    using BitManipulatorImpl = manipulator::BitManipulator<memory_t>;
    BitManipulatorImpl bm{};
    constexpr static memory_t size() { return bite_size_base::base::number_of_bites_v; }
  };
}// namespace base

template<std::size_t N, typename memory_t = uint8_t>
class _BitArrayBase_Array_t : public base::_BitArrayBase_t<N, memory_t>
{

  constexpr auto fill() -> void
  {
    for (auto i = 0; i < this->_v.size(); i++) { _v[i] = memory_t{}; }
  }

public:
  using base_1 = typename base::_BitArrayBase_t<N, memory_t>;
  using base_2 = typename base_1::bite_size_base;
  using base_1::size;
  using raw_memory_t = std::array<memory_t, base_2::memory_size_rounded_up_v>;


  template<std::size_t _N, typename _memory_t>
  friend std::ostream &operator<<(std::ostream &, const _BitArrayBase_Array_t<_N, _memory_t> &);

  constexpr explicit _BitArrayBase_Array_t() { fill(); };
  alignas(memory_t) raw_memory_t _v;

  void set(memory_t bit)
  {
    const auto index = static_cast<memory_t>(bit / base_2::memory_t_digits);
    const auto element = (bit + base_2::memory_t_digits * index) % base_2::memory_t_digits;
    this->_v[index] = this->bm.set(element, std::move(this->_v));// MG Check if this is correct!
    //_v[index] = _v[index] | (static_cast<memory_t>(1) << element);
  }
};

template<std::size_t N, typename memory_t> class _BitArrayBase_SameSize_t : public base::_BitArrayBase_t<N, memory_t>
{
public:
  using base_1 = typename base::_BitArrayBase_t<N, memory_t>;
  using base_2 = typename base_1::bite_size_base;
  using base_1::size;
  using raw_memory_t = memory_t;

  template<std::size_t _N, typename _memory_t>
  friend std::ostream &operator<<(std::ostream &, const _BitArrayBase_SameSize_t<_N, _memory_t> &);
  alignas(raw_memory_t) raw_memory_t _v{};

  void set(memory_t bit) { this->_v = this->bm.set(bit, std::move(this->_v)); }
  void clear(memory_t bit) { this->_v = this->bm.clear(bit, std::move(this->_v)); }
  bool get(memory_t bit) { return this->bm.get(bit, std::move(this->_v)); }
};


using BitArray64_t = _BitArrayBase_SameSize_t<_64, uint64_t>;
using BitArray32_t = _BitArrayBase_SameSize_t<_32, uint32_t>;
using BitArray16_t = _BitArrayBase_SameSize_t<_16, uint16_t>;
using BitArray8_t = _BitArrayBase_SameSize_t<_8, uint8_t>;

template<std::size_t _N, std::size_t CompareN, typename TrueT, typename FalseT>
using conditional_size_t = std::conditional_t<_N == CompareN, TrueT, FalseT>;

template<std::size_t _N, typename T> using conditional_size8_t = conditional_size_t<_N, _8, BitArray8_t, T>;

template<std::size_t _N, typename T>
using conditional_size16_t = conditional_size_t<_N, _16, BitArray16_t, conditional_size8_t<_N, T>>;

template<std::size_t _N, typename T>
using conditional_size32_t = conditional_size_t<_N, _32, BitArray32_t, conditional_size16_t<_N, T>>;

template<std::size_t _N, typename T>
using conditional_size64_t = conditional_size_t<_N, _64, BitArray64_t, conditional_size32_t<_N, T>>;

template<std::size_t _N> using self_configure_size_array_t = conditional_size64_t<_N, uint8_t>;

template<std::size_t _N, typename T> using self_configure_size_memory_t_t = conditional_size64_t<_N, T>;

}// namespace mgtl
