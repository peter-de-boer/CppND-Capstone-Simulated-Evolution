#ifndef EVOLUTION_H
#define EVOLUTION_H

#include <random>
#include "controller.h"
#include "renderer.h"
#include "microbe.h"

class Evolution {
 public:
  Evolution(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);

 private:
  
  std::vector<std::vector<bool>> _food;
  std::vector<Microbe> _microbes; // smart pointers?
 
};

#endif