#pragma once

#include <span>
#include <SDL3/SDL_init.h>
#include <string>

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
  
  struct Metadata {
    const std::string& name {};
    const std::string& version {};
    const std::string& identifier {};
  };

  class Instance {
    public:
      explicit Instance(std::span<Flags> flags);
      ~Instance();
    private:
  };

}
