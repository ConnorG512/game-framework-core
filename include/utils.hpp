#pragma once

#include <span>
#include <type_traits>
#include <utility>

namespace Utils
{
template <typename T>
concept EnumClass = std::is_enum_v<T>;

template <EnumClass T> auto or_flags(std::span<T> flags)
{
  if (flags.empty())
    return;

  return [flags]
  {
    auto result{0};
    for (const auto &flag : flags)
      result |= std::to_underlying(flag);

    return result;
  }();
}
} // namespace Utils
