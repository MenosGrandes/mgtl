#include <inttypes.h>

#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <mgtl/bit_array/bit_array_details.hpp>
#include <mgtl/bit_array/bit_manipulator.hpp>
#include <mgtl/bit_array/bit_size.hpp>
#include <mgtl/bit_array/type_traits.hpp>
#include <mgtl/type_traits/type_traits.hpp>
#pragma once
using namespace mgtl::type_traits;
using namespace mgtl::bit_array::type_traits;
using namespace mgtl::bit_array::details;
namespace mgtl::bit_array {
template<std::size_t _N, typename memory_t>
using BitArray = typename std::conditional_t<is_same_bite_size_v<_N, memory_t>,
  self_configure_size_memory_t_t<_N, memory_t>,
  _BitArrayBase_Array_t<_N, memory_t>>;


template<std::size_t _N>
using BitArray_t =
  typename std::conditional_t<is_buildin_v<_N>, self_configure_size_array_t<_N>, _BitArrayBase_Array_t<_N>>;

}// namespace mgtl
