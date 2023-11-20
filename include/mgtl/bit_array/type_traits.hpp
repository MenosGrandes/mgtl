#include <functional>
#include <limits>
#include <mgtl/bit_array/constants.hpp>
#include <mgtl/type_traits/type_traits.hpp>
#include <type_traits>

#pragma once

namespace mgtl::bit_array::type_traits {

using namespace mgtl::type_traits;
using namespace mgtl::bit_array::constants;

template<std::size_t NUMBER_OF_BITS, typename _memory_t, class Enable = void>
struct is_same_bite_size_t : public std::false_type
{
};

template<std::size_t NUMBER_OF_BITS, typename _memory_t>
struct is_same_bite_size_t<NUMBER_OF_BITS,
  _memory_t,
  typename std::enable_if_t<and_v<is_integer_but_not_zero_t<std::size_t, NUMBER_OF_BITS>,
    is_true_t<std::numeric_limits<_memory_t>::digits == NUMBER_OF_BITS>>>> : public std::true_type
{
};

template<std::size_t NUMBER_OF_BITS, typename memory_t>
static constexpr auto is_same_bite_size_v = is_same_bite_size_t<NUMBER_OF_BITS, memory_t>::value;


template<std::size_t NUMBER_OF_BITS>
static constexpr auto is_buildin_v = is_one_of_v<i_const_t<NUMBER_OF_BITS>, _64_t, _32_t, _16_t, _8_t>;

template<std::size_t NUMBER_OF_BITS, class Enable = void> struct is_buildin_size_t : public std::false_type
{
};

template<std::size_t NUMBER_OF_BITS>
struct is_buildin_size_t<NUMBER_OF_BITS, typename std::enable_if_t<is_buildin_v<NUMBER_OF_BITS>>>
  : public std::true_type
{
};

template<std::size_t NUMBER_OF_BITS> static constexpr auto is_buildin_size_v = is_buildin_size_t<NUMBER_OF_BITS>::value;



}// namespace mgtl::bit_array::type_traits
