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

using namespace mgtl::type_traits;
using mgtl::bit_array::bite_size::size_type;
namespace mgtl::bit_array::details {


template<std::size_t NUMBER_OF_BITS, typename memory_t = uint8_t>
class _BitArrayDifferentSize_t : public base::_BitArrayBase_t<NUMBER_OF_BITS, memory_t>
{


public:
  using base_1 = typename base::_BitArrayBase_t<NUMBER_OF_BITS, memory_t>;
  using base_2 = typename base_1::bite_size_base;
  using raw_memory_t = std::array<memory_t, base_2::memory_size_rounded_up_v>;


  template<std::size_t _NUMBER_OF_BITS, typename _memory_t>
  friend std::ostream &operator<<(std::ostream &, const _BitArrayDifferentSize_t<_NUMBER_OF_BITS, _memory_t> &);

  constexpr explicit _BitArrayDifferentSize_t() { fill(); };

  constexpr void set(size_type bit)
  {
    auto [index, element] = get_element(bit);
    this->_data[index] = base_1::BitManipulatorImpl::set(element, std::move(this->_data[index]));
  }
  constexpr auto get(size_type bit) -> bool
  {
    auto [index, element] = get_element(bit);
    return base_1::BitManipulatorImpl::get(element, std::move(this->_data[index]));
  }
  constexpr auto operator[](size_type bit) -> bool { return get(bit); }
  constexpr auto clear(size_type bit) -> void
  {
    auto [index, element] = get_element(bit);
    this->_data[index] = base_1::BitManipulatorImpl::clear(element, std::move(this->_data[index]));
  }
  constexpr auto popcount()
  {
    // MenosGrandes std::accumulate?
    size_type counter{ 0 };
     for (memory_t i : _data) {
    //for (size_type i = 0; i < base_2::memory_size_whole_v; i++) {
      counter += base_1::BitManipulatorImpl::popcount(i);
    }
    return counter;
  }

  constexpr auto fill() -> void
  {
    for (size_type i = 0; i < this->_data.size(); ++i) { _data[i] = memory_t{}; }
  }
  static constexpr auto get_element(size_type bit) -> std::tuple<size_type, size_type>
  {
    const size_type index = static_cast<size_type>(bit / base_1::memory_t_digits);
    const size_type element = static_cast<size_type>((bit + base_1::memory_t_digits * index) % base_1::memory_t_digits);
    return { index, element };
  }
private:
  alignas(memory_t) raw_memory_t _data;
};


}// namespace mgtl::bit_array::details
