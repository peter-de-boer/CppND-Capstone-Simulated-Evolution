#ifndef MICROBE_H
#define MICROBE_H

#include <vector>

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


class Gene {
  public:
    Gene();
  
  private:
    std::vector<float> _gene;
};

class Microbe {
  public:
    Microbe();
    Microbe(Microbe& parent);
    void Live();
  
  private:
  
    int _energy;
    Direction _direction;
    Gene _gene; 
};

#endif