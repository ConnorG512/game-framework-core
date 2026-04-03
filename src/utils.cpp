#include "utils.hpp"

#include <SDL3/SDL_version.h>
#include <format>

std::string GFC::Utils::get_version() noexcept { return std::format("{};{}", SDL_GetRevision(), SDL_GetVersion()); }
