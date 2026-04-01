#include "SDL3/SDL_init.h"
#include "init.hpp"
#include "utils.hpp"

#include <cassert>

Init::Instance::Instance(std::span<Flags> flags, const Metadata &app_data)
{
  const auto init_result{Utils::or_flags<Flags, SDL_InitFlags>(flags)};
  SDL_Init(init_result);
}

Init::Instance::~Instance() { SDL_Quit(); }

void Init::Instance::set_metadata(const Metadata &app_data) const noexcept
{
  for (const auto &str : {app_data.name, app_data.version, app_data.identifier})
    assert(!str.empty());

  SDL_SetAppMetadata(app_data.name.c_str(), app_data.version.c_str(), app_data.identifier.c_str());
}
