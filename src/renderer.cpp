#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "renderer.hpp"

GFC::Renderer::Instance::Instance(SDL_Window &window)
    : current_window_(window), renderer_(SDL_CreateRenderer(&window, nullptr), &SDL_DestroyRenderer)
{
}

void GFC::Renderer::Instance::draw(const Math::Vec4<float> &colors) noexcept
{
  SDL_SetRenderDrawColorFloat(renderer_.get(), colors.x, colors.y, colors.z, colors.w);
  SDL_RenderClear(renderer_.get());
  SDL_RenderPresent(renderer_.get());
}
