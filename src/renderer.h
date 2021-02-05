#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "params.h"
#include "microbe.h"
#include "microbelist.h"

class Renderer {
 public:
  Renderer(std::shared_ptr<ConfigParams> config_params);
  ~Renderer();
  void Render(std::shared_ptr<MicrobeList> microbe_list, std::shared_ptr<Food> food);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  std::shared_ptr<ConfigParams> _config_params;
};

#endif