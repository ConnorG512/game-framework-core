#pragma once

#include <concepts>
#include <expected>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vulkan/vulkan_core.h>

namespace GFC::Ren
{
template <typename Func, typename Ret, typename... Args>
concept VK_Func = std::is_invocable_v<Func, Args...> && std::same_as<std::invoke_result_t<Func, Args...>, Ret>;

template <typename Func, typename... Args>
  requires VK_Func<Func, VkResult, Args...>
[[nodiscard]] std::expected<void, std::string_view> vk_exec(Func &&func, Args &&...args)
{
  const auto result{std::forward<Func>(func)(std::forward<Args>(args)...)};
  if (result != VK_SUCCESS)
    return std::unexpected(get_vk_err(result));
  else
    return {};
}

[[nodiscard]] std::string_view get_vk_err(const VkResult vk_result) noexcept;
}; // namespace GFC::Ren
