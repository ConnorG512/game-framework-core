#pragma once

#include <cassert>
#include <cstdint>
#include <span>
#include <type_traits>
#include <utility>

namespace GFC::Bitset
{
template <typename T>
concept EnumType = std::is_enum_v<T>;

template <EnumType EnumT, std::integral MaskSize = std::uint32_t>
MaskSize create_bitmask(const std::span<const EnumT> flags) noexcept
{
  static_assert(sizeof(flags) >= sizeof(MaskSize));

  const MaskSize final_bitmask = [flags] -> MaskSize
  {
    MaskSize result{0};
    for (const auto &flag : flags)
      result |= std::to_underlying(flag);

    return result;
  }();

  return final_bitmask;
}

bool is_active_bit(std::integral auto bitcontainer, EnumType auto enum_flag) noexcept
{
  const auto flag_value{std::to_underlying(enum_flag)};
  return (bitcontainer & flag_value) != 0;
}

void toggle_bit(std::integral auto &bitcontainer, EnumType auto enum_flag) noexcept
{
  bitcontainer ^= std::to_underlying(enum_flag);
}
} // namespace GFC::Bitset
