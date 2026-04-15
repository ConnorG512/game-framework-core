#include "SDL3/SDL_error.h"
#include "SDL3/SDL_video.h"
#include "bitmasking.hpp"
#include "window/instance.hpp"

#include <cassert>
#include <expected>
#include <format>
#include <memory>
#include <span>
#include <utility>

namespace
{
[[nodiscard]] std::expected<std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>, std::string>
create_window(const std::string &title, std::pair<std::int32_t, std::int32_t> wh,
              const std::span<const SDL_WindowFlags> flags, VkInstance vk_instance, VkSurfaceKHR *vk_surface,
              const VkAllocationCallbacks *allocator = nullptr)
{
  assert(vk_surface != nullptr && "Invalid vk_surface in create_window");
  assert(!flags.empty() && "Flags passed cannot be empty!");

  auto new_window{
      SDL_CreateWindow(title.c_str(), wh.first, wh.second, GFC::Bitset::create_bitmask(flags) | SDL_WINDOW_VULKAN)};
  if (new_window == nullptr)
    return std::unexpected(std::format("Failed to create new window! Error: {}.", SDL_GetError()));
  if (!SDL_Vulkan_CreateSurface(new_window, vk_instance, allocator, vk_surface))
    return std::unexpected(std::format("Failed to create Vulkan surface! Error: {}.", SDL_GetError()));

  return std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>(new_window, &SDL_DestroyWindow);
}
} // namespace

GFC::Window::Instance::Instance(const std::string &title, std::pair<std::int32_t, std::int32_t> wh,
                                const std::span<const SDL_WindowFlags> window_flags, VkInstance vk_instance,
                                VkSurfaceKHR &vk_surface, Logger::Instance *logger)
    : window_(create_window(title.c_str(), wh, window_flags, vk_instance, &vk_surface)
                  .value_or({nullptr, &SDL_DestroyWindow}))
{
  assert(window_ != nullptr && "window member variable was nullptr!");
}
