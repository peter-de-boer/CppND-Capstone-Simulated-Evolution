#include "controller.h"

#include <iostream>



Controller::Controller() {
};

void Controller::HandleInput(bool &running, std::shared_ptr<ConfigParams> config_params,
                             std::vector<SDL_Rect> boxes) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
       if (e.button.button == SDL_BUTTON_LEFT) {     
         
         int x, y;
         SDL_GetMouseState(&x, &y);
         auto inside = [](int x, int y, SDL_Rect box) { 
           return ( x > box.x ) && 
                  ( x < box.x + box.w ) && 
                  ( y > box.y ) && 
                  ( y < box.y + box.h ); 
         };
         
         if (inside(x,y,boxes[0])) {
           config_params->food_distribution = kLines;
         } else if (inside(x,y,boxes[1])) {
           config_params->food_distribution = kUniform;
         } else if (inside(x,y,boxes[2])) {
           config_params->food_distribution = kRectangle;
         }

       }
    }        
  }
}