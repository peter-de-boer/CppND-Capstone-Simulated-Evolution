#include "microbe.h"



Microbe::Microbe(int x, int y, int energy, Direction direction, 
                 std::shared_ptr<ConfigParams> config_params) : 
                 _x(x), _y(y), _direction(direction),
                 _config_params(config_params) {
};

Microbe::Microbe(const Microbe& microbe) {
};

Microbe& Microbe::operator=(const Microbe& microbe) {
}

void Microbe::Live() {

};

// return a new microbe with the same genes, but slightly mutated
Microbe Microbe::Reproduce() {
  _energy = _energy / 2;
  Microbe child = Microbe(*this);
  return child;
};

