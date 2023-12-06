#include <inttypes.h>

#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <mgtl/bit_array/bit_manipulator.hpp>
#include <mgtl/bit_array/bit_size.hpp>
#include <mgtl/bit_array/type_traits.hpp>
#include <mgtl/type_traits/type_traits.hpp>

#pragma once

using namespace mgtl::type_traits;
using mgtl::bit_array::bite_size::size_type;
namespace mgtl::bit_array::details {

namespace base {
  template<std::size_t NUMBER_OF_BITS, typename memory_t>
  struct _BitArrayBase_t : public bite_size::bite_size<NUMBER_OF_BITS, memory_t>
  {
    using bite_size_base = bite_size::bite_size<NUMBER_OF_BITS, memory_t>;
    using BitManipulatorImpl = bit_manipulator::BitManipulator<memory_t>;
    constexpr static size_type size() { return bite_size_base::base::number_of_bites_v; }
  };
}// namespace base

}// namespace mgtl::bit_array::details
