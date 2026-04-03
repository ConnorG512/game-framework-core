#pragma once 

#include "SDL3/SDL_render.h"

#include <memory>

// Forward
class SDL_Window;
//

namespace GFC::Renderer
{
class Instance
{
public:
  explicit Instance(SDL_Window &window);
  
  void draw() noexcept;
private:
  SDL_Window &current_window_;
  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer_{SDL_CreateRenderer(&current_window_, nullptr),
                                                                          &SDL_DestroyRenderer};
};
} // namespace GFC::Renderer
