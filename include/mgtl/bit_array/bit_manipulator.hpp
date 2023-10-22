#pragma once

namespace mgtl {

namespace manipulator {
  template<typename memory_t> struct BitManipulator
  {
    constexpr static memory_t set(memory_t bit, memory_t _data)
    {
      return static_cast<memory_t>((_data | (static_cast<memory_t>(1) << bit)));
    }
    constexpr static memory_t toogle(memory_t bit, memory_t _data)
    {
      return static_cast<memory_t>((_data | (static_cast<memory_t>(1) << bit)));
    }
    constexpr static memory_t clear(memory_t bit, memory_t _data)
    {
      return static_cast<memory_t>(_data & ~(static_cast<memory_t>(1) << bit));
    }

    constexpr static memory_t check(memory_t bit, memory_t _data)
    {
      return ((_data | (static_cast<memory_t>(1) << bit)));
    }
    constexpr static bool get(memory_t bit, memory_t &&_data)
    {
      return static_cast<bool>((_data >> bit) & static_cast<memory_t>(1));
    }
  };
}// namespace manipulator
}// namespace mgtl
