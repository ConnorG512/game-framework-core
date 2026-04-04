#include "easy-window/builder.hpp"
#include "SDL3/SDL_video.h"

GFC::EasyWindow::Builder& GFC::EasyWindow::Builder::set_window_title(const std::string& window_title) noexcept
{
  window_title_ = window_title;
  return *this;
}

GFC::EasyWindow::Builder& GFC::EasyWindow::Builder::set_window_dimensions(const std::pair<const std::int32_t, const std::int32_t> wh) noexcept
{
  wh_ = wh;
  return *this;
}

GFC::EasyWindow::Builder& GFC::EasyWindow::Builder::set_fullscreen(const bool is_fullscreen) noexcept
{
  flags.push_back(SDL_WINDOW_FULLSCREEN);
  return *this;
}

GFC::EasyWindow::Builder& GFC::EasyWindow::Builder::set_always_on_top(const bool is_always_on_top) noexcept
{
  if(is_always_on_top) 
    flags.push_back(SDL_WINDOW_ALWAYS_ON_TOP);
  else {};
  
  return *this;
}

GFC::EasyWindow::Builder& GFC::EasyWindow::Builder::set_maximized(const bool is_maximized) noexcept
{
  if(is_maximized) 
    flags.push_back(SDL_WINDOW_MAXIMIZED);
  else {};

  return *this;
}

GFC::EasyWindow::Builder& GFC::EasyWindow::Builder::set_high_pixel_density(const bool using_high_pixel_density) noexcept
{
  if(using_high_pixel_density)
    flags.push_back(SDL_WINDOW_HIGH_PIXEL_DENSITY);
  else {};
  
  return *this;
}

GFC::EasyWindow::Instance GFC::EasyWindow::Builder::build() const
{
}
