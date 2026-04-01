#include "SDL3/SDL_error.h"
#include "SDL3/SDL_video.h"
#include "utils.hpp"

#include "window.hpp"
#include <cassert>
#include <format>
#include <utility>

Window::Instance::Instance(const std::string &title, std::pair<std::int32_t, std::int32_t> xy,
                           const std::span<const Flags> flags)
    : title{title.c_str()}, xy_{xy.first, xy.second},
      window_instance_{SDL_CreateWindow(title.c_str(), xy_.first, xy_.second, Utils::or_flags(flags)),
                       &SDL_DestroyWindow}
{
}

[[nodiscard]] std::expected<std::pair<std::int32_t, std::int32_t>, std::string>
Window::Instance::get_current_window_size() const noexcept
{
  assert(window_instance_ != nullptr && "window_instance_ is null during function \"get_current_window_size\"");

  auto width{0};
  auto height{0};

  if (SDL_GetWindowSize(window_instance_.get(), &width, &height))
    return std::unexpected(std::format("Window Error: {}", SDL_GetError()));
  else
  {
    assert(width > 0 && height > 0 && "Width or heght holds a value of [0] in \"get_current_window_size\"");
    return std::make_pair(width, height);
  }
}

[[nodiscard]] std::expected<std::pair<std::int32_t, std::int32_t>, std::string>
Window::Instance::get_current_window_position() const noexcept
{
  assert(window_instance_ != nullptr && "window_instance_ is null during function \"get_current_window_position\"");

  auto x{0};
  auto y{0};

  if (!SDL_GetWindowPosition(window_instance_.get(), &x, &y))
    return std::unexpected(std::format("Window Error: {}", SDL_GetError()));
  else
    return std::make_pair(x, y);
}

[[nodiscard]] std::expected<std::pair<std::int32_t, std::int32_t>, std::string>
Window::Instance::get_max_size() const noexcept
{
  assert(window_instance_ != nullptr && "window_instance_ is null during function \"get_current_window_position\"");

  auto x{0};
  auto y{0};

  if (!SDL_GetWindowMaximumSize(window_instance_.get(), &x, &y))
    return std::unexpected(std::format("Window Error: {}", SDL_GetError()));
  else
  {
    assert(x > 0 && y > 0 && "Width or heght holds a value of [0] in \"get_max_size\"");
    return std::make_pair(x, y);
  }
}

[[nodiscard]] std::expected<std::pair<std::int32_t, std::int32_t>, std::string>
Window::Instance::get_min_size() const noexcept
{
  assert(window_instance_ != nullptr && "window_instance_ is null during function \"get_current_window_position\"");

  auto x{0};
  auto y{0};

  if (!SDL_GetWindowMinimumSize(window_instance_.get(), &x, &y))
    return std::unexpected(std::format("Window Error: {}", SDL_GetError()));
  else
    return std::make_pair(x, y);
}

[[nodiscard]] std::expected<SDL_WindowID, std::string> Window::Instance::get_id() const noexcept
{
  assert(window_instance_ != nullptr && "window_instance_ is null during function \"get_id\"");

  const auto window_id{SDL_GetWindowID(window_instance_.get())};
  if (window_id == 0)
    return std::unexpected(std::format("Window Error: {}", SDL_GetError()));
  else
    return window_id;
}
