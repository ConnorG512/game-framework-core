#include "init.hpp"
#include "utils.hpp"
#include "SDL3/SDL_init.h"

Init::Instance::Instance(std::span<Flags> flags)
{
  const auto init_result {Utils::or_flags<Flags, SDL_InitFlags>(flags)};
    SDL_Init(init_result);   
}

Init::Instance::~Instance()
{
  SDL_Quit();
}
