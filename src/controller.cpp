#include "controller.h"

#include <iostream>



Controller::Controller() {
};

void Controller::HandleInput(bool &running, std::shared_ptr<ConfigParams> config_params, SDL_Rect box) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
       if (e.button.button == SDL_BUTTON_LEFT) {     
         
         int x, y;
         SDL_GetMouseState(&x, &y);
         if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) ) {
           config_params->food_distribution = kLines;
         }

       }
    }        
  }
}