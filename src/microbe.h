#ifndef MICROBE_H
#define MICROBE_H

#include <vector>
#include <random>

#include "gene.h"

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
    Microbe();
    Microbe(Microbe& parent);
    void Live();
    Microbe Reproduce();
  
  private:
  
    int _energy;
    Direction _direction;
    Gene _gene; 
};

#endif