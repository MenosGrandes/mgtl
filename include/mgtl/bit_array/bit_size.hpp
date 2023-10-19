#include <functional>
#include <limits>
#include <mgtl/bit_array/type_traits.hpp>
#include <mgtl/type_traits/type_traits.hpp>
#include <type_traits>
#pragma once

using namespace mgtl::type_traits;
using namespace mgtl::bit_array::type_traits;

namespace mgtl::bit_array::bite_size {

template<std::size_t N, typename _memory_t> struct bite_size_base
{
  using memory_t = _memory_t;
  constexpr static auto memory_t_digits = std::numeric_limits<memory_t>::digits;
  constexpr static auto memory_size_whole_v = N / memory_t_digits;
  constexpr static auto number_of_bites_v = N;
};
template<std::size_t N, typename _memory_t, class IsMemortTSameSizeAsN = void> struct bite_size
{
};
template<std::size_t N, typename _memory_t>
struct bite_size<N, _memory_t, typename std::enable_if_t<!is_same_bite_size_v<N, _memory_t>>>
  : public bite_size_base<N, _memory_t>
{
  using base = bite_size_base<N, _memory_t>;
  using base::memory_t_digits;
  using typename base::memory_t;
  using base::memory_size_whole_v;
  using base::number_of_bites_v;
};


template<std::size_t N, typename _memory_t>
struct bite_size<N, _memory_t, typename std::enable_if_t<is_same_bite_size_v<N, _memory_t>>>
  : public bite_size_base<N, _memory_t>
{
  using base = bite_size_base<N, _memory_t>;
  using base::memory_t_digits;
  using typename base::memory_t;
  using base::memory_size_whole_v;
  using base::number_of_bites_v;

  constexpr static auto memory_size_rest_v = N - (memory_t_digits * memory_size_whole_v);
  constexpr static auto memory_size_rounded_up_v = memory_size_whole_v + 1;
};

}// namespace mgtl::bit_array::bite_size
