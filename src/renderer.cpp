#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include <cassert>
#include "renderer.hpp"

GFC::Renderer::Instance::Instance(SDL_Window &window)
    : current_window_(window), renderer_(SDL_CreateRenderer(&window, nullptr), &SDL_DestroyRenderer)
{
}

void GFC::Renderer::Instance::draw(const Math::Vec4<float> &colors) noexcept
{
  for(const auto& color : {colors.x, colors.y, colors.z, colors.w})
    assert(color >= 0.0f && color <= 1.0f);

  SDL_SetRenderDrawColorFloat(renderer_.get(), colors.x, colors.y, colors.z, colors.w);
  SDL_RenderClear(renderer_.get());
  SDL_RenderPresent(renderer_.get());
}
