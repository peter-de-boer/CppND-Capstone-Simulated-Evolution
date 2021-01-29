#include "evolution.h"

Evolution::Evolution(std::shared_ptr<ConfigParams> config_params) : _config_params(config_params) {
    _disx = std::uniform_int_distribution<int>(0, _config_params->kGridWidth - 1);
    _disy = std::uniform_int_distribution<int>(0, _config_params->kGridHeight - 1);
};
  
void Evolution::Run(Controller const &controller, Renderer &renderer) {
  

  // start thread controller: wait for input
  // start thread for Renderer: update screen after each time step
  // start thread for food: spawn new food every time step
  // start thread for microbes
};