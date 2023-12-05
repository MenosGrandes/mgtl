#include <inttypes.h>

#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <mgtl/bit_array/details/bit_array_same_size.hpp>
#include <mgtl/bit_array/details/bit_array_different_size.hpp>
#include <mgtl/bit_array/bit_size.hpp>
#include <mgtl/bit_array/type_traits.hpp>
#include <mgtl/bit_array/type_traits.hpp>
#include <mgtl/type_traits/type_traits.hpp>
#pragma once
namespace mgtl::bit_array {

using namespace mgtl::type_traits;
using namespace mgtl::bit_array::type_traits;
using namespace mgtl::bit_array::details;
template<std::size_t NUMBER_OF_BITS, typename memory_t>
using BitArray = typename std::conditional_t<is_same_bite_size_v<NUMBER_OF_BITS, memory_t>,
  self_configure_size_memory_t_t<NUMBER_OF_BITS, memory_t>,
  _BitArrayDifferentSize_t<NUMBER_OF_BITS, memory_t>>;


template<std::size_t NUMBER_OF_BITS>
using BitArray_t = typename std::conditional_t<is_buildin_v<NUMBER_OF_BITS>,
  self_configure_size_array_t<NUMBER_OF_BITS>,
  _BitArrayDifferentSize_t<NUMBER_OF_BITS>>;

}// namespace mgtl::bit_array
