#include "microbe.h"

#include <iostream>

#include <thread>

Microbe::Microbe(int x, int y, int energy, int direction, 
                 std::shared_ptr<ConfigParams> config_params) : 
                 _x(x), _y(y), _energy(energy),
                 _direction(direction),
                 _config_params(config_params) {
  _gene.Randomize();
};

Microbe::Microbe(const Microbe& other) {
     _energy = other._energy;
    _x = other._x;
    _y = other._y;
    _direction = other._direction;
    _gene = other._gene;
    _config_params = other._config_params;
    _disx = other._disx;
    _disy = other._disy;
};

Microbe& Microbe::operator=(const Microbe& other) {
       _energy = other._energy;
    _x = other._x;
    _y = other._y;
    _direction = other._direction;
    _gene = other._gene;
    _config_params = other._config_params;
    _disx = other._disx;
    _disy = other._disy;
    return *this;
}


void Microbe::_Move() {
  // select change from gene
  int change_direction = _gene.GetSegment();
  int _direction = (_direction + change_direction) % 8;
  int dx, dy;
  switch (_direction) {
      case 0: dx = -1; dy =  1; break;
      case 1: dx =  0; dy =  1; break;
      case 2: dx =  1; dy =  1; break;
      case 3: dx =  1; dy =  0; break;
      case 4: dx =  1; dy = -1; break;
      case 5: dx =  0; dy = -1; break;
      case 6: dx = -1; dy = -1; break;
      case 7: dx = -1; dy =  0; break;
      default: dx = 0; dy = 0;
  }
  _x = (_x + dx) % _config_params->kGridWidth;
  _y = (_y + dy) % _config_params->kGridHeight;
  _energy -= _config_params->change_direction_energy[change_direction];
}

void Microbe::_Eat() {
}

bool Microbe::IsDead() const {
  return _energy <= 0;
}

void Microbe::Live() {
  while (!IsDead()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(_config_params->kMsPerMicrobeCycle));
    _Eat();
    _Reproduce();
    _Move();
  }
};

void Microbe::_Mutate() {
  _gene.Mutate();
}

// create a new microbe with the same genes, but slightly mutated
void Microbe::_Reproduce() {
  if (_energy >= _config_params->reproduce_energy) {
      _energy = _energy / 2;
      Microbe child = Microbe(*this);
    child._Mutate();
  //return child;
  // use a message queue?
  //  send child to message Queueu
  //  if queue receives a new child, add it to the list of microbes and trigger Live
  }
};

