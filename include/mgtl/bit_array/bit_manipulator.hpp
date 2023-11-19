#pragma once
#include "details/popcount.hpp"

namespace mgtl {

namespace manipulator {

  template<typename memory_t> struct BitManipulator
  {
    static constexpr auto _1 = static_cast<memory_t>(1);
    constexpr static memory_t set(memory_t bit, memory_t _data)
    {
      return static_cast<memory_t>((_data | (_1 << bit)));
    }
    constexpr static memory_t toogle(memory_t bit, memory_t _data)
    {
      return static_cast<memory_t>((_data | (_1 << bit)));
    }
    constexpr static memory_t clear(memory_t bit, memory_t _data)
    {
      return static_cast<memory_t>(_data & ~(_1 << bit));
    }

    constexpr static memory_t check(memory_t bit, memory_t _data)
    {
      return ((_data | (_1 << bit)));
    }
    constexpr static bool get(memory_t bit, memory_t &&_data)
    {
      return static_cast<bool>((_data >> bit) & _1);
    }
    constexpr static unsigned int popcount(memory_t _data) { return static_cast< unsigned int>(PopCount::popcount(_data)); }
  };
}// namespace manipulator
}// namespace mgtl
