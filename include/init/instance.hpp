#pragma once

#include <SDL3/SDL_init.h>
#include <functional>
#include <string>

namespace GFC::Init
{
// Forward
class Builder;
//

enum class Flags
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
  Instance(const GFC::Init::Builder &builder, std::function<void(const std::string &message)> log_callback);
  ~Instance();
};
} // namespace GFC::Init
