
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

namespace mgtl::bit_array::details {
using namespace mgtl::type_traits;

namespace base {
  template<std::size_t NUMBER_OF_BITS, typename memory_t>
  struct _BitArrayBase_t : public bite_size::bite_size<NUMBER_OF_BITS, memory_t>
  {
    using bite_size_base = bite_size::bite_size<NUMBER_OF_BITS, memory_t>;
    using BitManipulatorImpl = manipulator::BitManipulator<memory_t>;
    BitManipulatorImpl bm{};
    constexpr static memory_t size() { return bite_size_base::base::number_of_bites_v; }
  };
}// namespace base

template<std::size_t NUMBER_OF_BITS, typename memory_t = uint8_t>
class _BitArrayBase_Array_t : public base::_BitArrayBase_t<NUMBER_OF_BITS, memory_t>
{

  constexpr auto fill() -> void
  {
    for (memory_t i = 0; i < this->_data.size(); i++) { _data[i] = memory_t{}; }
  }
  constexpr auto get_element(memory_t bit) -> std::tuple<memory_t, memory_t>
  {

    const auto index = static_cast<memory_t>(bit / base_1::memory_t_digits);
    const memory_t element = static_cast<memory_t>((bit + base_1::memory_t_digits * index) % base_1::memory_t_digits);

    return { index, element };
  }

public:
  using base_1 = typename base::_BitArrayBase_t<NUMBER_OF_BITS, memory_t>;
  using base_2 = typename base_1::bite_size_base;
  using base_1::size;
  using raw_memory_t = std::array<memory_t, base_2::memory_size_rounded_up_v>;


  template<std::size_t _NUMBER_OF_BITS, typename _memory_t>
  friend std::ostream &operator<<(std::ostream &, const _BitArrayBase_Array_t<_NUMBER_OF_BITS, _memory_t> &);

  constexpr explicit _BitArrayBase_Array_t() { fill(); };
  alignas(memory_t) raw_memory_t _data;

  void set([[maybe_unused]] memory_t bit)
  {

    auto [index, element] = get_element(bit);
    this->_data[index] = this->bm.set(element, std::move(this->_data[index]));
  }
  auto get([[maybe_unused]] memory_t bit) -> bool
  {
    auto [index, element] = get_element(bit);
    return this->bm.get(element, std::move(this->_data[index]));
  }
  auto clear([[maybe_unused]] memory_t bit) -> void
  {
    auto [index, element] = get_element(bit);
    this->_data[index] = this->bm.clear(element, std::move(this->_data[index]));
  }
};

template<std::size_t NUMBER_OF_BITS, typename memory_t>
class _BitArrayBase_SameSize_t : public base::_BitArrayBase_t<NUMBER_OF_BITS, memory_t>
{
public:
  using base_1 = typename base::_BitArrayBase_t<NUMBER_OF_BITS, memory_t>;
  using base_2 = typename base_1::bite_size_base;
  using base_1::size;
  using raw_memory_t = memory_t;

  template<std::size_t _NUMBER_OF_BITS, typename _memory_t>
  friend std::ostream &operator<<(std::ostream &, const _BitArrayBase_SameSize_t<_NUMBER_OF_BITS, _memory_t> &);
  alignas(raw_memory_t) raw_memory_t _data{};

  void set(memory_t bit) { this->_data = this->bm.set(bit, std::move(this->_data)); }
  void clear(memory_t bit) { this->_data = this->bm.clear(bit, std::move(this->_data)); }
  bool get(memory_t bit) { return this->bm.get(bit, std::move(this->_data)); }
};


using BitArray64_t = _BitArrayBase_SameSize_t<_64, uint64_t>;
using BitArray32_t = _BitArrayBase_SameSize_t<_32, uint32_t>;
using BitArray16_t = _BitArrayBase_SameSize_t<_16, uint16_t>;
using BitArray8_t = _BitArrayBase_SameSize_t<_8, uint8_t>;

template<std::size_t NUMBER_OF_BITS, std::size_t CompareN, typename TrueT, typename FalseT>
using conditional_size_t = std::conditional_t<NUMBER_OF_BITS == CompareN, TrueT, FalseT>;

template<std::size_t NUMBER_OF_BITS, typename T>
using conditional_size8_t = conditional_size_t<NUMBER_OF_BITS, _8, BitArray8_t, T>;

template<std::size_t NUMBER_OF_BITS, typename T>
using conditional_size16_t =
  conditional_size_t<NUMBER_OF_BITS, _16, BitArray16_t, conditional_size8_t<NUMBER_OF_BITS, T>>;

template<std::size_t NUMBER_OF_BITS, typename T>
using conditional_size32_t =
  conditional_size_t<NUMBER_OF_BITS, _32, BitArray32_t, conditional_size16_t<NUMBER_OF_BITS, T>>;

template<std::size_t NUMBER_OF_BITS, typename T>
using conditional_size64_t =
  conditional_size_t<NUMBER_OF_BITS, _64, BitArray64_t, conditional_size32_t<NUMBER_OF_BITS, T>>;

template<std::size_t NUMBER_OF_BITS> using self_configure_size_array_t = conditional_size64_t<NUMBER_OF_BITS, uint8_t>;

template<std::size_t NUMBER_OF_BITS, typename T>
using self_configure_size_memory_t_t = conditional_size64_t<NUMBER_OF_BITS, T>;

}// namespace mgtl::bit_array::details
