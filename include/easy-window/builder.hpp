#pragma once 

#include "SDL3/SDL_video.h"
#include <string>
#include <utility>
#include <cstdint>
#include <vector>

namespace GFC::EasyWindow 
{
  class Instance; // Forward
  
  class Builder 
  {
    public:
      friend class EasyWindow::Instance;

      EasyWindow::Builder& set_window_title(const std::string& window_title = "Game Window") noexcept;
      EasyWindow::Builder& set_window_dimensions(const std::pair<const std::int32_t, const std::int32_t> wh = {1280, 720}) noexcept;
      EasyWindow::Builder& set_fullscreen(const bool is_fullscreen = false) noexcept;
      EasyWindow::Builder& set_always_on_top(const bool is_always_on_top = false) noexcept;
      EasyWindow::Builder& set_maximized(const bool is_maximized = false) noexcept;
      EasyWindow::Builder& set_high_pixel_density(const bool using_high_pixel_density = false) noexcept;
      EasyWindow::Instance build() const;

    private:
      std::string window_title_{};
      std::pair<std::int32_t, std::int32_t> wh_ {};
      std::vector<SDL_WindowFlags> flags {};
  };
}
