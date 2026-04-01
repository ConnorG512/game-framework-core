#pragma once

#include <expected>
#include <span>
#include <type_traits>
#include <utility>

namespace Utils
{
template <typename T>
concept EnumClass = std::is_enum_v<T>;

template <typename T>
concept Number = std::is_integral_v<T>;

enum class OrErrors
{
  FLAG_SET_EMPTY,
};
template <EnumClass FlagSet, Number OrType> std::expected<OrType, OrErrors> or_flags(std::span<FlagSet> flags) noexcept
{
  if (flags.empty())
    return std::unexpected(OrErrors::FLAG_SET_EMPTY);

  return [flags]
  {
    OrType result{0};
    for (const auto &flag : flags)
      result |= std::to_underlying(flag);

    return result;
  }();
}
} // namespace Utils
