#pragma once

#include <span>
#include <SDL3/SDL_init.h>

namespace Init
{
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

  class Instance {
    public:
      explicit Instance(std::span<Flags> flags);
      ~Instance();
    private:
  };

}
