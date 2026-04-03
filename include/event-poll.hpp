#pragma once

#include "SDL3/SDL_events.h"

#include <span>

namespace GFC::Event
{
void poll(bool finished, const std::span<const SDL_Event> event_list);
}
