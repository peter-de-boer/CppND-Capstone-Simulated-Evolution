#include "evolution.h"

Evolution::Evolution(std::shared_ptr<ConfigParams> config_params) : _config_params(config_params) {

};
  
void Evolution::_InitMicrobes() {
    std::uniform_int_distribution<int> disx = std::uniform_int_distribution<int>(0, _config_params->kGridWidth - 1);
    std::uniform_int_distribution<int> disy = std::uniform_int_distribution<int>(0, _config_params->kGridHeight - 1);
    std::uniform_int_distribution<int> disd = std::uniform_int_distribution<int>(0, 7);
    _microbes.emplace_back(Microbe(disx(_gen), disy(_gen), 100, disd(_gen), _config_params));
}

void Evolution::Run(Controller const &controller, Renderer &renderer) {
  
  _InitMicrobes();
  // start thread controller: wait for input
  // start thread for Renderer: update screen after each time step
  // start thread for food: spawn new food every time step
  // start thread for microbes
  for(auto microbe : _microbes) {
    microbe.Live();
  }
  
};