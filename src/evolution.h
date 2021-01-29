#ifndef EVOLUTION_H
#define EVOLUTION_H

#include <random>
#include <thread>

#include "controller.h"
#include "renderer.h"
#include "microbe.h"


class Evolution {
  public:
    Evolution(std::shared_ptr<ConfigParams> config_params);
    ~Evolution();
    void Run(Controller const &controller, Renderer &renderer);

  private:
    void _InitMicrobes();
  
    std::vector<std::vector<bool>> _food;
    std::vector<Microbe> _microbes; // smart pointers?
    std::shared_ptr<ConfigParams> _config_params;
  
    std::vector<std::thread> _threads;
  
    std::random_device _rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 _gen {_rd()}; //Standard mersenne_twister_engine seeded with rd()


};

#endif