#include "renderer.hpp"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

GFC::Renderer::Instance::Instance(SDL_Window &window)
  : current_window_(window)
  , renderer_(SDL_CreateRenderer(&window, nullptr), &SDL_DestroyRenderer) {}

void GFC::Renderer::Instance::draw() noexcept
{
  SDL_SetRenderDrawColorFloat(renderer_.get(), 0.5f, 0.5f, 0.5f, 1.0f);
  SDL_RenderClear(renderer_.get());
  SDL_RenderPresent(renderer_.get());
}
