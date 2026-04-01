#pragma once

#include <SDL3/SDL_init.h>
#include <span>
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

struct Metadata
{
  const std::string &name{"Application"};
  const std::string &version{"1.0"};
  const std::string &identifier{"com.application.myapplication"};
};

class Instance
{
public:
  Instance(std::span<Flags> flags, const Metadata &app_data);
  ~Instance();

private:
  void set_metadata(const Metadata &app_data) const noexcept;
};

} // namespace Init
