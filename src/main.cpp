#include <iostream>
#include "controller.h"
#include "evolution.h"
#include "renderer.h"
#include "params.h"

int main() {

  std::shared_ptr<ConfigParams> config_params = std::make_shared<ConfigParams>();

  std::cout << "Press the 1st(green) button to spawn food in lines\n";
  std::cout << "Press the 2nd(gray)  button to spawn food uniformly\n";
  std::cout << "Press the 3rd(pink)  button to spawn food in a rectangle\n";
  Renderer renderer(config_params);
  Controller controller;
  Evolution evolution(config_params);
  evolution.Run(controller, renderer);
  std::cout << "Evolution is finished!\n";
  return 0;
}