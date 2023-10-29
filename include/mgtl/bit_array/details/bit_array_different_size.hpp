#include <inttypes.h>

#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <mgtl/bit_array/bit_manipulator.hpp>
#include <mgtl/bit_array/bit_size.hpp>
#include <mgtl/bit_array/details/bit_array_base.hpp>
#include <mgtl/bit_array/type_traits.hpp>
#include <mgtl/type_traits/type_traits.hpp>

#pragma once

namespace mgtl::bit_array::details {
using namespace mgtl::type_traits;


template<std::size_t NUMBER_OF_BITS, typename memory_t = uint8_t>
class _BitArrayBase_Array_t : public base::_BitArrayBase_t<NUMBER_OF_BITS, memory_t>
{

  constexpr auto fill() -> void
  {
    for (typename decltype(_data)::size_type i = 0; i < this->_data.size(); i++) { _data[i] = memory_t{}; }
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

  constexpr void set(memory_t bit)
  {

    auto [index, element] = get_element(bit);
    this->_data[index] = base_1::BitManipulatorImpl::set(element, std::move(this->_data[index]));
  }
  constexpr auto get(memory_t bit) -> bool
  {
    auto [index, element] = get_element(bit);
    return base_1::BitManipulatorImpl::get(element, std::move(this->_data[index]));
  }
  constexpr auto clear(memory_t bit) -> void
  {
    auto [index, element] = get_element(bit);
    this->_data[index] = base_1::BitManipulatorImpl::clear(element, std::move(this->_data[index]));
  }
  constexpr auto popcount()
  {
    memory_t counter{0};
    for (auto i : _data)
    {
      counter+=base_1::BitManipulatorImpl::popcount(i);
    }
    return counter;

  }
};


}// namespace mgtl::bit_array::details
