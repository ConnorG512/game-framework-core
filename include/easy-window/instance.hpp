#pragma once

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "math/vec.hpp"

#include <expected>
#include <memory>

namespace GFC
{
namespace Logger
{
class Instance;
}
namespace EasyWindow
{
class Builder; // Forward

class Instance
{
public:
  Instance(const EasyWindow::Builder &builder, Logger::Instance *logger = nullptr);

  [[nodiscard]] std::expected<std::pair<std::int32_t, std::int32_t>, std::string>
  get_current_window_size() const noexcept;

  [[nodiscard]] std::expected<std::pair<std::int32_t, std::int32_t>, std::string>
  get_current_window_position() const noexcept;

  [[nodiscard]] std::expected<std::pair<std::int32_t, std::int32_t>, std::string> get_max_size() const noexcept;

  [[nodiscard]] std::expected<std::pair<std::int32_t, std::int32_t>, std::string> get_min_size() const noexcept;

  [[nodiscard]] std::expected<SDL_WindowID, std::string> get_id() const noexcept;

  void draw(const Math::Vec4<float> &colors) noexcept;

private:
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_{nullptr, &SDL_DestroyWindow};
  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer_{nullptr, &SDL_DestroyRenderer};
};
} // namespace GFC::EasyWindow
}; // namespace GFC
