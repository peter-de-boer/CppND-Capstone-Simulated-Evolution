#include "evolution.h"
#include <algorithm>

#include <iostream>

Evolution::Evolution(std::shared_ptr<ConfigParams> config_params) : _config_params(config_params) {

};

Evolution::~Evolution() {
    std::for_each(_threads.begin(), _threads.end(), [](std::thread &t) {
        t.join();
    });
}
  
void Evolution::_InitMicrobes() {
    std::uniform_int_distribution<int> disx = std::uniform_int_distribution<int>(0, _config_params->kGridWidth - 1);
    std::uniform_int_distribution<int> disy = std::uniform_int_distribution<int>(0, _config_params->kGridHeight - 1);
    std::uniform_int_distribution<int> disd = std::uniform_int_distribution<int>(0, 7);
    _microbes.emplace_back(std::make_shared<Microbe>(disx(_gen), disy(_gen), 100, disd(_gen), _config_params));
}

void Evolution::_Cleanup() {
  while (_microbes.size() > 0) {

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    _microbes.erase(
        std::remove_if(_microbes.begin(), _microbes.end(),
            [](const auto m) { return m->IsDead(); }), 
        _microbes.end()   
    );
  }
}

void Evolution::Run(Controller const &controller, Renderer &renderer) {
  
  _InitMicrobes();
  // start thread controller: wait for input
  // start thread for Renderer: update screen after each time step
  // start thread for food: spawn new food every time step
  // start thread for microbes
  for(auto microbe : _microbes) {
    _threads.emplace_back(std::thread(&Microbe::Live, microbe));
  }
  // start thread for cleaning up the list lof microbes
  std::thread t(&Evolution::_Cleanup, this);
  t.join();
  
};