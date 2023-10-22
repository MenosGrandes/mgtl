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

namespace mgtl::bit_array::details {
using namespace mgtl::type_traits;

namespace base {
  template<std::size_t NUMBER_OF_BITS, typename memory_t>
  struct _BitArrayBase_t : public bite_size::bite_size<NUMBER_OF_BITS, memory_t>
  {
    using bite_size_base = bite_size::bite_size<NUMBER_OF_BITS, memory_t>;
    using BitManipulatorImpl = manipulator::BitManipulator<memory_t>;
    constexpr static memory_t size() { return bite_size_base::base::number_of_bites_v; }
  };
}// namespace base

}// namespace mgtl::bit_array::details
