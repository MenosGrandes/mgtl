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
using namespace mgtl::bit_array::bite_size;

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

  constexpr void set(memory_t bit) { this->_data = base_1::BitManipulatorImpl::set(bit, std::move(this->_data)); }
  constexpr void clear(memory_t bit) { this->_data = base_1::BitManipulatorImpl::clear(bit, std::move(this->_data)); }
  constexpr bool get(memory_t bit) { return base_1::BitManipulatorImpl::get(bit, std::move(this->_data)); }
  constexpr  memory_t popcount() { return base_1::BitManipulatorImpl::popcount(std::move(this->_data)); }
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
