#pragma once

#include <SDL3/SDL_init.h>
#include <cstdint>

// Forward
namespace GFC
{
namespace Logger
{
class Instance;
}
//
namespace Init
{
class Builder;
}
} // namespace GFC
//

namespace GFC::Init
{
enum class Flags : std::uint32_t
{
  AUDIO = SDL_INIT_AUDIO,
  VIDEO = SDL_INIT_VIDEO,
  JOYSTICK = SDL_INIT_JOYSTICK,
  HAPTIC = SDL_INIT_HAPTIC,
  GAMEPAD = SDL_INIT_GAMEPAD,
  EVENTS = SDL_INIT_EVENTS,
  SENSOR = SDL_INIT_SENSOR,
  CAMERA = SDL_INIT_CAMERA,
};

class Instance
{
public:
  explicit Instance(const GFC::Init::Builder &builder, GFC::Logger::Instance *logger = nullptr);
  ~Instance();
};
} // namespace GFC::Init
