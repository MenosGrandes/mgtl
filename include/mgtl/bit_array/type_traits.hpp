#include <functional>
#include <limits>
#include <mgtl/bit_array/constants.hpp>
#include <mgtl/type_traits/type_traits.hpp>
#include <type_traits>

#pragma once

using namespace mgtl::type_traits;
using namespace mgtl::bit_array::constants;
namespace mgtl::bit_array::type_traits {


template<std::size_t N, typename _memory_t, class Enable = void> struct is_same_bite_size_t : public std::false_type
{
};

template<std::size_t N, typename _memory_t>
struct is_same_bite_size_t<N,
  _memory_t,
  typename std::enable_if_t<
    and_v<is_integer_but_not_zero_t<std::size_t, N>, is_true<std::numeric_limits<_memory_t>::digits == N>>>>
  : public std::true_type
{
};

template<std::size_t N, typename memory_t>
static constexpr auto is_same_bite_size_v = is_same_bite_size_t<N, memory_t>::value;


template<std::size_t N> static constexpr auto is_buildin_v = is_one_of_v<i_const_t<N>, _64_t, _32_t, _16_t, _8_t>;

template<std::size_t N, class Enable = void> struct is_buildin_size_t : public std::false_type
{
};

template<std::size_t N> struct is_buildin_size_t<N, typename std::enable_if_t<is_buildin_v<N>>> : public std::true_type
{
};

template<std::size_t N> static constexpr auto is_buildin_size_v = is_buildin_size_t<N>::value;
}// namespace mgtl::bit_array::type_traits
