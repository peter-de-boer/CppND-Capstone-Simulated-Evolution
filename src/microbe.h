#ifndef MICROBE_H
#define MICROBE_H

#include <vector>
#include <random>
#include <memory>

#include "gene.h"
#include "params.h"

enum Direction {
  kUp,
  kUpRight,
  kRight,
  kDownRight,
  kDown,
  kDownLeft,
  kLeft,
  kUpLeft 
};


class Microbe {
  public:
    Microbe(std::shared_ptr<ConfigParams> config_params);
    Microbe(const Microbe& parent);
    Microbe& operator=(const Microbe& parent);
    void Live();
    Microbe Reproduce();
  
  private:
    int _energy;
    Direction _direction;
    Gene _gene; 
    std::shared_ptr<ConfigParams> _config_params;
};

#endif