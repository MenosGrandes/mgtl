/*
 *
 * http://0x80.pl/articles/sse-popcount.html
 *
 * */
#include <limits>
#include <mgtl/functional/functional.hpp>
#include <mgtl/type_traits/type_traits.hpp>
#pragma once

using namespace mgtl::functional;
using namespace mgtl::type_traits;


struct PopCount
{
  template<typename memory_t> constexpr static unsigned int popcount(memory_t bits)
  {
    constexpr auto _digits = digits_v<memory_t>;
    if constexpr (is_less_and_equal(_digits, _digits_u)) {
      return static_cast<unsigned int>(__builtin_popcount(bits));
    } else if constexpr (is_less_and_equal(_digits_u, _digits_l)) {
      return static_cast<unsigned int>(__builtin_popcountl(bits));
    } else if constexpr (is_less_and_equal(_digits_l, _digits_ll)) {
      return static_cast<unsigned int>(__builtin_popcountll(bits));
    } else {
      static_assert(true, "Not known type");
      return 0;
    }
  }
};
