#include "SDL3/SDL_keyboard.h"
#include "input/input.hpp"
#include <cassert>
#include <utility>

bool GFC::Input::is_key_being_pressed(const ScanCode keypress) noexcept
{
  const auto *key_states{SDL_GetKeyboardState(nullptr)};
  assert(key_states != nullptr);

  return (key_states[std::to_underlying(keypress)]);
}
