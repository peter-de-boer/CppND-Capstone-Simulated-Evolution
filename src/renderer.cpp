#include "renderer.h"
#include <iostream>


Renderer::Renderer(std::shared_ptr<ConfigParams> config_params) : _config_params(config_params) {
  
    // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Simulated Evolution", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, _config_params->kScreenWidth,
                                _config_params->kScreenHeight, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
};

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
};

void Renderer::Render(std::shared_ptr<MicrobeList> microbe_list, 
                      std::shared_ptr<Food> food,
                      std::vector<SDL_Rect> boxes) {
  SDL_Rect block;
  block.w = _config_params->kScreenWidth / _config_params->kGridWidth;
  block.h = _config_params->kScreenHeight / _config_params->kGridHeight;
  int dw = block.w / 2;
  int dh = block.h / 2;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

 
  // Render microbes
  {
    std::lock_guard<std::mutex> lck(microbe_list->mx);
    for (auto microbe : microbe_list->microbes) {

      block.x = microbe->_x * block.w;
      block.y = microbe->_y * block.h;
      if (!microbe->IsDead()) {
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
      } else {
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0xFF, 0xFF);
      }
      SDL_RenderFillRect(sdl_renderer, &block);
    }
  }
  
  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  std::lock_guard<std::mutex> lock(food->mx);
  for (int x=0; x<_config_params->kGridWidth; ++x) {
     for (int y=0; y<_config_params->kGridHeight; ++y) {
      if (food->values[y][x]) {
        SDL_RenderDrawPoint(sdl_renderer, x*block.w+dw, y*block.h+dh);
      }
    }
  }

  
  // render buttons
  SDL_SetRenderDrawColor(sdl_renderer, 0xAA, 0xFF, 0xAA, 0xFF);
  SDL_RenderFillRect(sdl_renderer, &boxes[0]);
  
  SDL_SetRenderDrawColor(sdl_renderer, 0xAA, 0xAA, 0xAA, 0xFF);
  SDL_RenderFillRect(sdl_renderer, &boxes[1]);
  
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xAA, 0xAA, 0xFF);
  SDL_RenderFillRect(sdl_renderer, &boxes[2]);
      
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}