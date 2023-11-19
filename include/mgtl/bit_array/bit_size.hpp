#include <functional>
#include <limits>
#include <mgtl/bit_array/type_traits.hpp>
#include <mgtl/type_traits/type_traits.hpp>
#include <type_traits>
#pragma once


namespace mgtl::bit_array::bite_size {

using namespace mgtl::type_traits;
using namespace mgtl::bit_array::type_traits;

template<std::size_t NUMBER_OF_BITS, typename _memory_t> struct bite_size_base
{
  using memory_t = _memory_t;
  constexpr static auto memory_t_digits = std::numeric_limits<memory_t>::digits;
  constexpr static auto memory_size_whole_v = static_cast<memory_t>(NUMBER_OF_BITS / memory_t_digits);
  constexpr static auto number_of_bites_v = NUMBER_OF_BITS;
};
template<std::size_t NUMBER_OF_BITS, typename _memory_t, class IsMemortTSameSizeAsN = void> struct bite_size
{
};
template<std::size_t NUMBER_OF_BITS, typename _memory_t>
struct bite_size<NUMBER_OF_BITS, _memory_t, typename std::enable_if_t<is_same_bite_size_v<NUMBER_OF_BITS, _memory_t>>>
  : public bite_size_base<NUMBER_OF_BITS, _memory_t>
{
  using base = bite_size_base<NUMBER_OF_BITS, _memory_t>;
  using base::memory_t_digits;
  using typename base::memory_t;
  using base::memory_size_whole_v;
  using base::number_of_bites_v;
};


template<std::size_t NUMBER_OF_BITS, typename _memory_t>
struct bite_size<NUMBER_OF_BITS, _memory_t, typename std::enable_if_t<!is_same_bite_size_v<NUMBER_OF_BITS, _memory_t>>>
  : public bite_size_base<NUMBER_OF_BITS, _memory_t>
{
  using base = bite_size_base<NUMBER_OF_BITS, _memory_t>;
  using base::memory_t_digits;
  using typename base::memory_t;
  using base::memory_size_whole_v;
  using base::number_of_bites_v;

  constexpr static auto memory_size_rest_v =
    static_cast<memory_t>(NUMBER_OF_BITS - (memory_t_digits * memory_size_whole_v));
  constexpr static auto memory_size_rounded_up_v = memory_size_whole_v + 1;
};
/*
 *I need to distinguish between digits of type.
 * */


}// namespace mgtl::bit_array::bite_size
