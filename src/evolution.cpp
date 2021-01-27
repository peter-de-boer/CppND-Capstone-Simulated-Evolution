#include "evolution.h"

Evolution::Evolution(std::size_t grid_width, std::size_t grid_height) {
};
  
void Evolution::Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration) {
  // start thread controller: wait for input
  // start thread for Renderer: update screen after each time step
  // start thread for food: spawn new food every time step
  // start thread for microbes
};