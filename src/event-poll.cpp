#include "event-poll.hpp"

void Event::poll(bool finished, const std::span<const SDL_Event> event_list)
{
  while (!finished)
  {
    SDL_Event event{};

    while (SDL_PollEvent(&event))
    {
      for (const auto &event : event_list)
      {
        if (event.type == SDL_EVENT_QUIT)
        {
          finished = true;
        }
      }
    }
    // Game loop:
  }
}
