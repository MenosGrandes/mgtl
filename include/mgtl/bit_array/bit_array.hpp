#include <inttypes.h>

#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <mgtl/functional/functional.hpp>

#pragma  once
namespace mgtl
{
using namespace mgtl::functional;
namespace bit_array {

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



using _64_t = i_const_t<64>;
using _32_t = i_const_t<32>;
using _16_t = i_const_t<16>;
using _8_t = i_const_t<8>;


static constexpr auto _64 = i_const_v<64>;
static constexpr auto _32 = i_const_v<32>;
static constexpr auto _16 = i_const_v<16>;
static constexpr auto _8 = i_const_v<8>;


namespace bite_size {
  template<std::size_t N, typename _memory_t> struct bite_size
  {
    using memory_t = _memory_t;
    constexpr static auto memory_t_digits = std::numeric_limits<memory_t>::digits;
    constexpr static auto memory_size_whole_v = N / memory_t_digits;
    constexpr static auto memory_size_rest_v = N - (memory_t_digits * memory_size_whole_v);
    constexpr static auto memory_size_rounded_up_v = memory_size_whole_v + (memory_size_rest_v > 0 ? 1 : 0);
    constexpr static auto number_of_bites_v = N;
    constexpr static bool same_bite_size_v = (memory_t_digits == number_of_bites_v);
  };
  template<typename _memory_t> struct bite_size<0, _memory_t>
  {
    // static_assert(false, "Cannot use 0 bites.");
  };

  template<std::size_t NumberOfBites, typename _memory_t, class Enable = void>
  struct is_same_bite_size_t : public std::false_type
  {
  };

  template<typename _memory_t> struct is_same_bite_size_t<0, _memory_t, void> : public std::false_type
  {
    // static_assert(false, "Cannot use 0 bites.");
  };

  template<std::size_t NumberOfBites, typename _memory_t>
  struct is_same_bite_size_t<NumberOfBites,
    _memory_t,
    typename std::enable_if_t<bite_size<NumberOfBites, _memory_t>::same_bite_size_v>> : public std::true_type
  {
  };

  template<std::size_t N, typename memory_t>
  static constexpr auto is_same_bite_size_v = is_same_bite_size_t<N, memory_t>::value;



  template<std::size_t N> static constexpr auto is_buildin_v = is_one_of_v<i_const_t<N>, _64_t, _32_t, _16_t, _8_t>;

  template<std::size_t N, class Enable = void> struct is_buildin_size_t : public std::false_type
  {
  };

  template<std::size_t N>
  struct is_buildin_size_t <N, typename std::enable_if_t<is_buildin_v<N>>> : public std::true_type
  {
  };

  template<std::size_t N>
  static constexpr auto is_buildin_size_v = is_buildin_size_t<N>::value;

}// namespace bite_size

namespace base {
  template<std::size_t N, typename memory_t> struct BitArrayBase : public bite_size::bite_size<N, memory_t>
  {
    using bite_size_base = bite_size::bite_size<N, memory_t>;
    using BitManipulatorImpl = manipulator::BitManipulator<memory_t>;
    BitManipulatorImpl bm{};
  };
}// namespace base

template<std::size_t N, typename memory_t> class BitArrayBase_Array : public base::BitArrayBase<N, memory_t>
{
  using base = typename base::BitArrayBase<N, memory_t>::bite_size_base;
  using raw_memory_t = std::array<memory_t, base::memory_size_rounded_up_v>;

  constexpr auto fill() -> void
  {
    for (auto i = 0; i < this->_v.size(); i++) { _v[i] = memory_t{}; }
  }

public:
  template<std::size_t _N, typename _memory_t>
  friend std::ostream &operator<<(std::ostream &, const BitArrayBase_Array<_N, _memory_t> &);

  constexpr explicit BitArrayBase_Array() { fill(); };
  alignas(memory_t) raw_memory_t _v;

  void set(memory_t bit)
  {
    constexpr auto index_max = base::memory_size_rounded_up_v - 1;
    const auto index = static_cast<memory_t>(bit / base::memory_t_digits);
    const auto element = (bit + base::memory_t_digits * index) % base::memory_t_digits;
    this->_v[index] = this->bm.set(element, std::move(this->_v));// MG Check if this is correct!
    //_v[index] = _v[index] | (static_cast<memory_t>(1) << element);
  }
};

template<std::size_t N, typename memory_t> class BitArrayBase_SameSize : public base::BitArrayBase<N, memory_t>
{
  using base = typename base::BitArrayBase<N, memory_t>::bite_size_base;
  using raw_memory_t = memory_t;

public:
  template<std::size_t _N, typename _memory_t>
  friend std::ostream &operator<<(std::ostream &, const BitArrayBase_SameSize<_N, _memory_t> &);
  alignas(raw_memory_t) raw_memory_t _v{};

  void set(memory_t bit) { this->_v = this->bm.set(bit, std::move(this->_v)); }
  void clear(memory_t bit) { this->_v = this->bm.clear(bit, std::move(this->_v)); }
  bool get(memory_t bit) { return this->bm.get(bit, std::move(this->_v)); }
};


namespace printer {

  template<std::size_t _N, typename _memory_t>
  std::ostream &operator<<(std::ostream &os, const BitArrayBase_SameSize<_N, _memory_t> &L)
  {
    os << "[ " << L._v << " ]\n";

    return os;
  }
  template<std::size_t _N, typename _memory_t>
  std::ostream &operator<<(std::ostream &os, const BitArrayBase_Array<_N, _memory_t> &L)
  {
    os << "[ ";
    for (auto it : L._v) { os << it << " "; }
    os << "]\n";
    return os;
  }

  struct PrintAsBytes
  {
    template<std::size_t _N, typename _memory_t> static std::string print(const BitArrayBase_Array<_N, _memory_t> &l)
    {
      using bite_array_t = BitArrayBase_Array<_N, _memory_t>;
      std::string s;

      size_t counter = 0;
      for (auto whole = 0; whole < bite_array_t::memory_size_whole_v; whole++) {
        for (auto digit = 0; digit < bite_array_t::memory_t_digits; digit++) {
          const auto _char = (((l._v[whole] >> counter) & static_cast<_memory_t>(1)) ? '1' : '0');
          s += _char;
          counter++;
        }
      }

      for (auto rest = 0; rest < bite_array_t::memory_size_rest_v; rest++) {
        const auto _char =
          (((l._v[bite_array_t::memory_size_whole_v] >> counter) & static_cast<_memory_t>(1)) ? '1' : '0');
        s += _char;
        counter++;
      }
      return s;
    }

    template<std::size_t _N, typename _memory_t> static std::string print(const BitArrayBase_SameSize<_N, _memory_t> &l)
    {
      std::string s;
      for (auto c = 0; c < _N; c++) {
        const auto _char = (((l._v >> c) & static_cast<_memory_t>(1)) ? '1' : '0');
        s += _char;
      }
      return s;
    }
  };
}// namespace printer


using BitArray64_t = BitArrayBase_SameSize<_64, uint64_t>;
using BitArray32_t = BitArrayBase_SameSize<_32, uint32_t>;
using BitArray16_t = BitArrayBase_SameSize<_16, uint16_t>;
using BitArray8_t = BitArrayBase_SameSize<_8, uint8_t>;

namespace conditional {
  template<std::size_t _N, std::size_t CompareN, typename TrueT, typename FalseT>
  using conditional_size_t = std::conditional_t<_N == CompareN, TrueT, FalseT>;

  template<std::size_t _N, typename T> using conditional_size8_t = conditional_size_t<_N, _8, BitArray8_t, T>;

  template<std::size_t _N, typename T>
  using conditional_size16_t = conditional_size_t<_N, _16, BitArray16_t, conditional_size8_t<_N, T>>;

  template<std::size_t _N, typename T>
  using conditional_size32_t = conditional_size_t<_N, _32, BitArray32_t, conditional_size16_t<_N, T>>;

  template<std::size_t _N, typename T>
  using conditional_size64_t = conditional_size_t<_N, _64, BitArray64_t, conditional_size32_t<_N, T>>;
}// namespace conditional
}// namespace bit_array

template<std::size_t _N, typename memory_t>
using BitArray = typename std::conditional_t<bit_array::bite_size::is_same_bite_size_v<_N, memory_t>,
  mgtl::bit_array::conditional::conditional_size64_t<_N, memory_t>,
  bit_array::BitArrayBase_Array<_N, memory_t>>;



template<std::size_t _N>
using BitArray_t = typename std::conditional_t<bit_array::bite_size::is_buildin_v<_N>,
  bit_array::conditional::conditional_size64_t<_N, uint8_t>,
  bit_array::BitArrayBase_Array<_N, uint8_t>>;

}
