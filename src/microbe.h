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
    int _x;
    int _y;
    Direction _direction;
    Gene _gene; 
    std::shared_ptr<ConfigParams> _config_params;
    std::random_device _rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 _gen {_rd()}; //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<int> _disx;
    std::uniform_int_distribution<int> _disy;
};

#endif