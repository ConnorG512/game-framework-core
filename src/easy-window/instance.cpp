#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "bitmasking.hpp"
#include "easy-window/builder.hpp"
#include "easy-window/instance.hpp"
#include "logging.hpp"

#include <cassert>
#include <cstdint>
#include <format>
#include <utility>

GFC::EasyWindow::Instance::Instance(const EasyWindow::Builder &builder, GFC::Logger::Instance *logger)
    : window_(SDL_CreateWindow(builder.window_title_.c_str(), builder.wh_.first, builder.wh_.second,
                               GFC::Bitset::create_bitmask<SDL_WindowFlags, std::uint64_t>(builder.flags)),
              &SDL_DestroyWindow),
      renderer_(SDL_CreateRenderer(window_.get(), nullptr), &SDL_DestroyRenderer)
{
  if (logger != nullptr)
  {
    logger->write_to_logger(std::format("Window Title: {}.", builder.window_title_), GFC::Logger::LogType::DEBUG);
    logger->write_to_logger(std::format("Width: {}, Height: {}.", builder.wh_.first, builder.wh_.second),
                            GFC::Logger::LogType::DEBUG);
  }
};

[[nodiscard]] std::expected<std::pair<std::int32_t, std::int32_t>, std::string>
GFC::EasyWindow::Instance::get_current_window_size() const noexcept
{
  assert(window_ != nullptr && "window_ is null during function \"get_current_window_size\"");

  auto width{0};
  auto height{0};

  if (SDL_GetWindowSize(window_.get(), &width, &height))
    return std::unexpected(std::format("Window Error: {}", SDL_GetError()));
  else
  {
    assert(width > 0 && height > 0 && "Width or heght holds a value of [0] in \"get_current_window_size\"");
    return std::make_pair(width, height);
  }
}

[[nodiscard]] std::expected<std::pair<std::int32_t, std::int32_t>, std::string>
GFC::EasyWindow::Instance::get_current_window_position() const noexcept
{
  assert(window_ != nullptr && "window_ is null during function \"get_current_window_position\"");

  auto x{0};
  auto y{0};

  if (!SDL_GetWindowPosition(window_.get(), &x, &y))
    return std::unexpected(std::format("Window Error: {}", SDL_GetError()));
  else
    return std::make_pair(x, y);
}

[[nodiscard]] std::expected<std::pair<std::int32_t, std::int32_t>, std::string>
GFC::EasyWindow::Instance::get_max_size() const noexcept
{
  assert(window_ != nullptr && "window_ is null during function \"get_current_window_position\"");

  auto x{0};
  auto y{0};

  if (!SDL_GetWindowMaximumSize(window_.get(), &x, &y))
    return std::unexpected(std::format("Window Error: {}", SDL_GetError()));
  else
  {
    assert(x > 0 && y > 0 && "Width or heght holds a value of [0] in \"get_max_size\"");
    return std::make_pair(x, y);
  }
}

[[nodiscard]] std::expected<std::pair<std::int32_t, std::int32_t>, std::string>
GFC::EasyWindow::Instance::get_min_size() const noexcept
{
  assert(window_ != nullptr && "window_ is null during function \"get_current_window_position\"");

  auto x{0};
  auto y{0};

  if (!SDL_GetWindowMinimumSize(window_.get(), &x, &y))
    return std::unexpected(std::format("Window Error: {}", SDL_GetError()));
  else
    return std::make_pair(x, y);
}

[[nodiscard]] std::expected<SDL_WindowID, std::string> GFC::EasyWindow::Instance::get_id() const noexcept
{
  assert(window_ != nullptr && "window_ is null during function \"get_id\"");

  const auto window_id{SDL_GetWindowID(window_.get())};
  if (window_id == 0)
    return std::unexpected(std::format("Window Error: {}", SDL_GetError()));
  else
    return window_id;
}

void GFC::EasyWindow::Instance::draw(const Math::Vec4<float> &colors) noexcept
{
  for (const auto &color : {colors.x, colors.y, colors.z, colors.w})
    assert(color >= 0.0f && color <= 1.0f);

  SDL_SetRenderDrawColorFloat(renderer_.get(), colors.x, colors.y, colors.z, colors.w);
  SDL_RenderClear(renderer_.get());
  SDL_RenderPresent(renderer_.get());
}
