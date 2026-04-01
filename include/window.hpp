#pragma once

#include "SDL3/SDL_video.h"

#include <SDL3/SDL.h>
#include <cstdint>
#include <expected>
#include <memory>
#include <span>
#include <utility>

namespace Window
{
enum class Flags : std::uint64_t
{
  FULLSCREEN = SDL_WINDOW_FULLSCREEN,
  OPENGL = SDL_WINDOW_OPENGL,
  HIDDEN = SDL_WINDOW_HIDDEN,
  BORDERLESS = SDL_WINDOW_BORDERLESS,
  RESIZEABLE = SDL_WINDOW_RESIZABLE,
  MINIMIZED = SDL_WINDOW_MINIMIZED,
  MAXIMIZED = SDL_WINDOW_MAXIMIZED,
  MOUSE_GRABBED = SDL_WINDOW_MOUSE_GRABBED,
  INPUT_FOCUS = SDL_WINDOW_INPUT_FOCUS,
  MOUSE_FOCUS = SDL_WINDOW_MOUSE_FOCUS,
  EXTERNAL = SDL_WINDOW_EXTERNAL,
  MODAL = SDL_WINDOW_MODAL,
  HIGH_PIXEL_DENSITY = SDL_WINDOW_HIGH_PIXEL_DENSITY,
  MOUSE_CAPTURE = SDL_WINDOW_MOUSE_CAPTURE,
  ALWAYS_ON_TOP = SDL_WINDOW_ALWAYS_ON_TOP,
  UTILITY = SDL_WINDOW_UTILITY,
  TOOLTIP = SDL_WINDOW_TOOLTIP,
  POPUP_MENU = SDL_WINDOW_POPUP_MENU,
  KEYBOARD_GRABBED = SDL_WINDOW_KEYBOARD_GRABBED,
  VULKAN = SDL_WINDOW_VULKAN,
  METAL = SDL_WINDOW_METAL,
  TRANSPARENT = SDL_WINDOW_TRANSPARENT,
  NOT_FOCUSABLE = SDL_WINDOW_NOT_FOCUSABLE,
};

class Instance
{
public:
  const char *title{"Game Window"};

  [[nodiscard]] std::expected<std::pair<std::int32_t, std::int32_t>, std::string>
  get_current_window_size() const noexcept;
  [[nodiscard]] std::expected<std::pair<std::int32_t, std::int32_t>, std::string>
  get_current_window_position() const noexcept;
  [[nodiscard]] std::expected<std::pair<std::int32_t, std::int32_t>, std::string> get_max_size() const noexcept;
  [[nodiscard]] std::expected<std::pair<std::int32_t, std::int32_t>, std::string> get_min_size() const noexcept;
  [[nodiscard]] std::expected<SDL_WindowID, std::string> get_id() const noexcept;

private:
  Instance(const std::string &title, std::pair<std::int32_t, std::int32_t> xy, const std::span<const Flags> flags);

  std::pair<std::int32_t, std::int32_t> xy_{1280, 720};
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_instance_{
      SDL_CreateWindow(title, xy_.first, xy_.second, 0), &SDL_DestroyWindow};
};
}; // namespace Window
