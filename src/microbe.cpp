#include "microbe.h"

#include <iostream>

Microbe::Microbe(int x, int y, int energy, Direction direction, 
                 std::shared_ptr<ConfigParams> config_params) : 
                 _x(x), _y(y), _energy(energy),
                 _direction(direction),
                 _config_params(config_params) {
  std::cout << "_x: " << _x << "\n";
  std::cout << "_y: " << _y << "\n";
  std::cout << "_energy: " << _energy << "\n";
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
  _energy += -10;
}

void Microbe::_Eat() {
}

bool Microbe::_IsDead() {
  return _energy <= 0;
}

void Microbe::Live() {
  std::cout << "_energy: " << _energy << "\n";
  while (!_IsDead()) {
    _Eat();
    _Reproduce();
    _Move();
    std::cout << _energy << " ";
  }
  std::cout << "\n";

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

