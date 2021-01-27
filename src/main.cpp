#include <iostream>
#include "controller.h"
#include "evolution.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Evolution evolution(kGridWidth, kGridHeight);
  evolution.Run(controller, renderer, kMsPerFrame);
  std::cout << "Evolution is finished!\n";
  return 0;
}