#ifndef MICROBE_H
#define MICROBE_H

#include <vector>
#include <random>
#include <memory>

#include "gene.h"
#include "params.h"
#include "queue.h"
#include "food.h"


class Microbe {
  public:
    Microbe();
    Microbe(int x, int y, int energy, int direction, 
            std::shared_ptr<Food> food,
            std::shared_ptr<ConfigParams> config_params,
            std::shared_ptr<MessageQueue<Microbe>> new_microbes,
            std::shared_ptr<MessageQueue<std::thread::id>> thread_ids);
    Microbe(const Microbe& other);
    Microbe& operator=(const Microbe& other);
    Microbe(Microbe &&other);
    Microbe &operator=(Microbe &&other);
    void Live();
    bool IsDead() const;
  
    int _x;
    int _y;
    
    
  
  private:
    
    void _Mutate();
    void _Reproduce();
    void _Move();
    void _Eat();
    int _energy;
    
    int _direction;
    Gene _gene; 
    std::shared_ptr<ConfigParams> _config_params;
    std::random_device _rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 _gen {_rd()}; //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<int> _disx;
    std::uniform_int_distribution<int> _disy;
    std::shared_ptr<Food> _food;
    std::shared_ptr<MessageQueue<Microbe>> _new_microbes;
    std::shared_ptr<MessageQueue<std::thread::id>> _thread_ids;
  
};

#endif