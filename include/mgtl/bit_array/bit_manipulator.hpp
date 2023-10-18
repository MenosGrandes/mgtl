#pragma once

namespace mgtl
{

namespace manipulator {
  template<typename memory_t> struct BitManipulator
  {
    memory_t set(memory_t bit, memory_t _v) const
    {
      return static_cast<memory_t>((_v | (static_cast<memory_t>(1) << bit)));
    }
    memory_t toogle(memory_t bit, memory_t _v) const
    {
      return static_cast<memory_t>((_v | (static_cast<memory_t>(1) << bit)));
    }
    memory_t clear(memory_t bit, memory_t _v) const
    {
      return static_cast<memory_t>(_v & ~(static_cast<memory_t>(1) << bit));
    }

    memory_t check(memory_t bit, memory_t _v) const { return ((_v | (static_cast<memory_t>(1) << bit))); }
    bool get(memory_t bit, memory_t &&_v) const { return static_cast<bool>((_v >> bit) & static_cast<memory_t>(1)); }
  };
}// namespace manipulator
}
