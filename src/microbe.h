#ifndef MICROBE_H
#define MICROBE_H

#include <vector>
#include <random>
#include <memory>

#include "gene.h"
#include "params.h"
#include "direction.h"


class Microbe {
  public:
    Microbe(int x, int y, int energy, Direction direction, std::shared_ptr<ConfigParams> config_params);
    Microbe(const Microbe& other);
    Microbe& operator=(const Microbe& other);
    void Live();
    
  
  private:
    void _Mutate();
    void _Reproduce();
    void _Move();
    void _Eat();
    bool _IsDead();
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