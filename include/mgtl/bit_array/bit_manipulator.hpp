#pragma once
#include <mgtl/bit_array/details/popcount.hpp>

#include <mgtl/bit_array/bit_size.hpp>
using mgtl::bit_array::bite_size::size_type;
namespace mgtl::bit_manipulator {


template<typename memory_t> struct BitManipulator
{
  static constexpr auto _1 = static_cast<memory_t>(1);
  constexpr static memory_t set(size_type bit, memory_t _data) { return static_cast<memory_t>((_data | (_1 << bit))); }
  constexpr static memory_t toogle(size_type bit, memory_t _data)
  {
    return static_cast<memory_t>((_data | (_1 << bit)));
  }
  constexpr static memory_t clear(size_type bit, memory_t _data) { return static_cast<memory_t>(_data & ~(_1 << bit)); }

  constexpr static memory_t check(size_type bit, memory_t _data) { return ((_data | (_1 << bit))); }
  constexpr static bool get(size_type bit, memory_t &&_data) { return static_cast<bool>((_data >> bit) & _1); }
  constexpr static size_type popcount(memory_t _data)
  {
    return static_cast<size_type>(bit_array::PopCount::popcount(_data));
  }
};
}// namespace mgtl::bit_manipulator
