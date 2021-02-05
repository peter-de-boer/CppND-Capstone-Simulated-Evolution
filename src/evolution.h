#ifndef EVOLUTION_H
#define EVOLUTION_H

#include <random>
#include <thread>

#include "controller.h"
#include "renderer.h"
#include "microbe.h"
#include "queue.h"
#include "food.h"
#include "microbelist.h"


class Evolution {
  public:
    Evolution(std::shared_ptr<ConfigParams> config_params);
    ~Evolution();
    void Run(Controller const &controller, Renderer &renderer);

  private:
    void _InitMicrobes();
    void _InitFood();
    void _Add_New_Microbes();
    void _Cleanup();
    void _CleanupThreads();
    void _SpawnFood();
    void _SpawnFoodUniform();
    void _SpawnFoodLines();
    void _Render(Controller const &controller, Renderer &renderer);
  
    std::shared_ptr<Food> _food;
    std::shared_ptr<MicrobeList> _microbe_list;
   
    std::shared_ptr<ConfigParams> _config_params;
    std::shared_ptr<MessageQueue<Microbe>> _new_microbes;
    std::shared_ptr<MessageQueue<std::thread::id>> _thread_ids;
    
    std::vector<std::thread> _threads;
    std::mutex _threads_mutex;
  
    std::random_device _rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 _gen {_rd()}; //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> _disr {std::uniform_real_distribution<>(0.0, 1.0)};


};

#endif