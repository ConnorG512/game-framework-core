#pragma once

#include <span>
#include <string>
#include <type_traits>
#include <utility>

namespace GFC::Utils
{
template <typename T>
concept EnumClass = std::is_enum_v<T>;

template <typename T>
concept Number = std::is_integral_v<T>;

template <EnumClass FlagSet, Number OrType> OrType or_flags(const std::span<const FlagSet> flags) noexcept
{
  OrType result{0};
  for (const auto &flag : flags)
    result |= std::to_underlying(flag);

  return result;
}

std::string get_version() noexcept;
} // namespace GFC::Utils
