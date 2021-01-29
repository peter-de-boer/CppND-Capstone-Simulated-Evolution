#include <iostream>
#include "controller.h"
#include "evolution.h"
#include "renderer.h"
#include "params.h"

int main() {

  std::shared_ptr<ConfigParams> config_params = std::make_shared<ConfigParams>();

  Renderer renderer(config_params);
  Controller controller;
  Evolution evolution(config_params);
  evolution.Run(controller, renderer);
  std::cout << "Evolution is finished!\n";
  return 0;
}