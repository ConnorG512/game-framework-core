#include "easy-window/instance.hpp"
#include "event-poll.hpp"
#include "colors.hpp"

void GFC::Event::start_loop(bool &finished, GFC::EasyWindow::Instance &window)
{
  while (!finished)
  {
    SDL_Event event{};

    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_EVENT_QUIT)
        finished = true;
    }
    // Game loop:
    window.draw(GFC::Colors::BLUE);
  }
}
