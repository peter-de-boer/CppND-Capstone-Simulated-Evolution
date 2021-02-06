#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include "SDL.h"
#include "params.h"

class Controller {
 public:
   Controller();
    void HandleInput(bool &running, std::shared_ptr<ConfigParams> config_params, 
                     std::vector<SDL_Rect> boxes) const;
  
 private:

};

#endif