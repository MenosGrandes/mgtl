
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <mgtl/type_traits/type_traits.hpp>
#include <mgtl/bit_array/type_traits.hpp>
#include <mgtl/bit_array/bit_array_details.hpp>
#include <mgtl/bit_array/bit_array.hpp>
#include <mgtl/bit_array/constants.hpp>
#include <limits>
using namespace mgtl;
using namespace mgtl::type_traits;
using namespace mgtl::bit_array;
using namespace mgtl::bit_array::bite_size;
using namespace mgtl::bit_array::type_traits;
using namespace mgtl::bit_array::constants;

#define TEST_TYPES                                                                                           \
  BitArray64_t, BitArray32_t, BitArray16_t, BitArray8_t, (BitArray<64, uint64_t>), (BitArray<32, uint32_t>), \
    (BitArray<16, uint16_t>), (BitArray<8, uint8_t>)
#define TEST_TYPES_I_CONST_SAME_SIZE (integral_const_t<uint8_t,8>),(integral_const_t<uint16_t,16>),(integral_const_t<uint32_t,32>),(integral_const_t<uint64_t,64>)
#define TEST_TYPES_I_CONST_DIFF_SIZE (integral_const_t<uint8_t,12>),(integral_const_t<uint8_t,16>),(integral_const_t<uint16_t,8>),(integral_const_t<uint32_t,8>),(integral_const_t<uint64_t,63>)

#define TEST_TYPES_I_CONST_DIFF_SIZE_2 (integral_const_t<uint8_t,3>),(integral_const_t<uint8_t,2>),(integral_const_t<uint16_t,80>),(integral_const_t<uint32_t,80>),(integral_const_t<uint64_t,325>)
TEMPLATE_TEST_CASE("memory_t same size types, explicit", "[tag]", TEST_TYPES)
{
    using BitArray = TestType;
    static constexpr auto N = BitArray::number_of_bites_v;
    using memory_t = typename BitArray::memory_t;

  STATIC_REQUIRE(BitArray::memory_t_digits == N);

  STATIC_REQUIRE(std::is_same_v<typename BitArray::base::memory_t, typename BitArray::memory_t>);
  STATIC_REQUIRE(std::is_same_v<typename BitArray::base_1::memory_t,typename  BitArray::memory_t>);
  STATIC_REQUIRE(std::is_same_v<typename BitArray::base_2::memory_t,typename  BitArray::memory_t>);
  STATIC_REQUIRE(std::is_same_v<typename BitArray::memory_t, memory_t>);

  STATIC_REQUIRE(BitArray::base_1::base::memory_t_digits == std::numeric_limits<memory_t>::digits);
  STATIC_REQUIRE(BitArray::base_1::memory_t_digits == BitArray::memory_t_digits);
  STATIC_REQUIRE(BitArray::base_1::memory_t_digits == BitArray::base::memory_t_digits);
  STATIC_REQUIRE(BitArray::base_1::memory_t_digits == BitArray::base_2::memory_t_digits);

  STATIC_REQUIRE(BitArray::base::memory_size_whole_v == BitArray::memory_size_whole_v);
  STATIC_REQUIRE(BitArray::base_1::memory_size_whole_v ==BitArray::memory_size_whole_v );
  STATIC_REQUIRE(BitArray::base_2::memory_size_whole_v == BitArray::memory_size_whole_v);
  STATIC_REQUIRE(BitArray::memory_size_whole_v == 1);

  STATIC_REQUIRE(BitArray::base::number_of_bites_v == BitArray::number_of_bites_v);
  STATIC_REQUIRE(BitArray::base_1::number_of_bites_v ==BitArray::number_of_bites_v);
  STATIC_REQUIRE(BitArray::base_2::number_of_bites_v ==BitArray::number_of_bites_v);
  STATIC_REQUIRE(BitArray::number_of_bites_v == N);
}

TEMPLATE_TEST_CASE("memory_t size types, implicit from integral constant", "[tag]", TEST_TYPES_I_CONST_SAME_SIZE, TEST_TYPES_I_CONST_DIFF_SIZE)
{

  static constexpr auto N = TestType::value;
  using memory_t = typename TestType::value_type;
  using BitArray = BitArray<N,memory_t>;

  static constexpr auto MEMORY_T_DIGITS = std::numeric_limits<memory_t>::digits;
  STATIC_REQUIRE(std::is_same_v<typename BitArray::base::memory_t, typename BitArray::memory_t>);
  STATIC_REQUIRE(std::is_same_v<typename BitArray::base_1::memory_t,typename  BitArray::memory_t>);
  STATIC_REQUIRE(std::is_same_v<typename BitArray::base_2::memory_t,typename  BitArray::memory_t>);
  STATIC_REQUIRE(std::is_same_v<typename BitArray::memory_t, memory_t>);

  STATIC_REQUIRE(BitArray::base_1::base::memory_t_digits == MEMORY_T_DIGITS);
  STATIC_REQUIRE(BitArray::base_1::memory_t_digits == BitArray::memory_t_digits);
  STATIC_REQUIRE(BitArray::base_1::memory_t_digits == BitArray::base::memory_t_digits);
  STATIC_REQUIRE(BitArray::base_1::memory_t_digits == BitArray::base_2::memory_t_digits);

  STATIC_REQUIRE(BitArray::memory_size_whole_v == static_cast<memory_t>(N/MEMORY_T_DIGITS));
  STATIC_REQUIRE(BitArray::base::memory_size_whole_v == BitArray::memory_size_whole_v);
  STATIC_REQUIRE(BitArray::base_1::memory_size_whole_v ==BitArray::memory_size_whole_v );
  STATIC_REQUIRE(BitArray::base_2::memory_size_whole_v == BitArray::memory_size_whole_v);

  STATIC_REQUIRE(BitArray::number_of_bites_v == N);
  STATIC_REQUIRE(BitArray::base::number_of_bites_v == BitArray::number_of_bites_v);
  STATIC_REQUIRE(BitArray::base_1::number_of_bites_v ==BitArray::number_of_bites_v);
  STATIC_REQUIRE(BitArray::base_2::number_of_bites_v ==BitArray::number_of_bites_v);
}

TEMPLATE_TEST_CASE("memory_size_rest_v && memory_size_rounded_up_v ", "[tag]", TEST_TYPES_I_CONST_DIFF_SIZE, TEST_TYPES_I_CONST_DIFF_SIZE_2)
{

  static constexpr auto N = TestType::value;
  using memory_t = typename TestType::value_type;
  using BitArray = BitArray<N,memory_t>;

  static constexpr auto MEMORY_T_DIGITS = std::numeric_limits<memory_t>::digits;
  static constexpr auto MEMORY_T_SIZE_WHOLE_V = static_cast<memory_t>(N/MEMORY_T_DIGITS);
  static constexpr auto MEMORY_SIZE_REST_V = static_cast<memory_t>(N - (MEMORY_T_DIGITS * MEMORY_T_SIZE_WHOLE_V));

  STATIC_REQUIRE(BitArray::memory_size_rest_v == MEMORY_SIZE_REST_V);
  STATIC_REQUIRE(BitArray::base_1::memory_size_rest_v ==BitArray::memory_size_rest_v );
  STATIC_REQUIRE(BitArray::base_2::memory_size_rest_v == BitArray::memory_size_rest_v);

  STATIC_REQUIRE(BitArray::memory_size_rounded_up_v == MEMORY_T_SIZE_WHOLE_V + 1);
  STATIC_REQUIRE(BitArray::base_1::memory_size_rounded_up_v ==BitArray::memory_size_rounded_up_v);
  STATIC_REQUIRE(BitArray::base_2::memory_size_rounded_up_v ==BitArray::memory_size_rounded_up_v);
}
