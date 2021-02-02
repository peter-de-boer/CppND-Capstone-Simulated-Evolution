#include "controller.h"
#include "SDL.h"

Controller::Controller() {
};

void Controller::HandleInput(bool &running) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    }
  }
}