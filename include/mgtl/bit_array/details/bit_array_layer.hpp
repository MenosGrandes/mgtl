
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
using namespace mgtl::bit_array::bite_size;
namespace mgtl::bit_array::details {

template<std::size_t NUMBER_OF_BITS_IN_LAYER, typename memory_t>
class _BitArrayLayer_t : public base::_BitArrayBase_t<NUMBER_OF_BITS_IN_LAYER, memory_t>
{

public:
  using base_1 = typename base::_BitArrayBase_t<NUMBER_OF_BITS_IN_LAYER, memory_t>;
  using base_2 = typename base_1::bite_size_base;
  using raw_memory_t = std::array<memory_t, base_2::memory_size_whole_v>;

private:
  alignas(memory_t) raw_memory_t _data;
};
/*
 *
 *  There are 4 layers to represent set bits
 *
 * */
template<std::size_t NUMBER_OF_BITS_OVERALL, typename memory_t>
class BitArrayWithLayers : public base::_BitArrayBase_t<NUMBER_OF_BITS_OVERALL, memory_t>
{
  // TEMP MENOSGRANDES!!
  static_assert(NUMBER_OF_BITS_OVERALL << 4 > 0, " NUMBER_OF_BITS_OVERALL must be dividable by 16 to 0");

public:
  using base_1 = typename base::_BitArrayBase_t<NUMBER_OF_BITS_OVERALL, memory_t>;
  using base_2 = typename base_1::bite_size_base;
  using base_1::size;
  using raw_memory_t = std::array<memory_t, base_2::memory_size_whole_v>;

private:
  alignas(memory_t) raw_memory_t _data;
  alignas(memory_t) _BitArrayLayer_t<NUMBER_OF_BITS_OVERALL << 1, memory_t> _layer_1;
  alignas(memory_t) _BitArrayLayer_t<NUMBER_OF_BITS_OVERALL << 2, memory_t> _layer_2;
  alignas(memory_t) _BitArrayLayer_t<NUMBER_OF_BITS_OVERALL << 3, memory_t> _layer_3;
  alignas(memory_t) _BitArrayLayer_t<NUMBER_OF_BITS_OVERALL << 4, memory_t> _layer_4;
};
}// namespace mgtl::bit_array::details
