#include "microbe.h"

#include <iostream>

#include <thread>

Microbe::Microbe() {
};

Microbe::Microbe(int x, int y, int energy, int direction, 
                 std::shared_ptr<Food> food,
                 std::shared_ptr<ConfigParams> config_params,
                 std::shared_ptr<MessageQueue<Microbe>> new_microbes,
                 std::shared_ptr<MessageQueue<std::thread::id>> thread_ids) : 
                 _x(x), _y(y), _energy(energy),
                 _direction(direction), 
                 _food(food),
                 _config_params(config_params),
                 _new_microbes(new_microbes),
                 _thread_ids(thread_ids) {
  _gene.Randomize();
};

Microbe::Microbe(const Microbe& other) {
    _energy = other._energy;
    _x = other._x;
    _y = other._y;
    _direction = other._direction;
    _food = other._food;
    _gene = other._gene;
    _config_params = other._config_params;
    _new_microbes = other._new_microbes;
    _thread_ids = other._thread_ids;
    _disx = other._disx;
    _disy = other._disy;
};

Microbe& Microbe::operator=(const Microbe& other) {
    _energy = other._energy;
    _x = other._x;
    _y = other._y;
    _direction = other._direction;
    _food = other._food;
    _gene = other._gene;
    _config_params = other._config_params;
    _new_microbes = other._new_microbes;
    _thread_ids = other._thread_ids;
    _disx = other._disx;
    _disy = other._disy;
    return *this;
}

Microbe::Microbe(Microbe &&other) {
    _energy = other._energy;
    _x = other._x;
    _y = other._y;
    _direction = other._direction;
    _food = other._food;
    _gene = other._gene;
    _config_params = other._config_params;
    _new_microbes = other._new_microbes;
    _thread_ids = other._thread_ids;
    _disx = other._disx;
    _disy = other._disy;
}

Microbe& Microbe::operator=(Microbe &&other) {
    if (this == &other) return *this;

    _energy = other._energy;
    _x = other._x;
    _y = other._y;
    _direction = other._direction;
    _food = other._food;
    _gene = other._gene;
    _config_params = other._config_params;
    _new_microbes = other._new_microbes;
    _thread_ids = other._thread_ids;
    _disx = other._disx;
    _disy = other._disy;

    return *this;
}


void Microbe::_Move() {
  // select change from gene
  int change_direction = _gene.GetSegment();
  _direction = (_direction + change_direction) % 8;
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
  if (_x < 0) _x += _config_params->kGridWidth;
  if (_y < 0) _y += _config_params->kGridHeight;
  _energy -= _config_params->change_direction_energy[change_direction];

}

void Microbe::_Eat() {
  std::lock_guard<std::mutex> lock(_food->mx);
  if ((_food->values)[_y][_x]) {
    (_food->values)[_y][_x] = false;
    _energy += _config_params->food_energy;
  }
}

bool Microbe::IsDead() const {
  return _energy <= 0;
}

void Microbe::_Spend_Energy() {
  _energy -= _config_params->timestep_energy;
}

void Microbe::Live() {
  while (!IsDead() && !_config_params->finished) {
    std::this_thread::sleep_for(std::chrono::milliseconds(_config_params->kMsPerMicrobeCycle));
    _Eat();
    _Reproduce();
    _Move();
    _Spend_Energy();
  } 
  _thread_ids->send(std::move(std::this_thread::get_id()));
};

void Microbe::_Mutate() {
  _gene.Mutate();
}

void Microbe::_RandomDirection() {
  _direction = _disd(_gen);
}

// if energy is high enough 
// create a new microbe with the same genes, but slightly mutated
// split energy between parent and child
void Microbe::_Reproduce() {
  if (_energy >= _config_params->reproduce_energy) {
      _energy = _energy / 2;
      Microbe child = Microbe(*this);
      child._Mutate();
      child._RandomDirection();
      _new_microbes->send(std::move(child));
  }
};

