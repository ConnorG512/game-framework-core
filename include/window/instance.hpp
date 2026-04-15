#pragma once

#include "SDL3/SDL_video.h"
#include "SDL3/SDL_vulkan.h"
#include <cstdint>
#include <memory>
#include <span>
#include <string>
#include <utility>

namespace GFC
{
namespace Logger
{
class Instance;
}
} // namespace GFC

namespace GFC::Window
{
class Instance
{
public:
  Instance(const std::string &title, std::pair<std::int32_t, std::int32_t> wh,
           const std::span<const SDL_WindowFlags> window_flags, VkInstance vk_instance,
                                VkSurfaceKHR &vk_surface, Logger::Instance *logger = nullptr);

private:
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_{nullptr, &SDL_DestroyWindow};
};
}; // namespace GFC::Window
