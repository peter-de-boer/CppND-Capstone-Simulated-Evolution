#include "evolution.h"
#include <algorithm>
#include <functional>
#include <future>

Evolution::Evolution(std::shared_ptr<ConfigParams> config_params) : _config_params(config_params) {
  _new_microbes = std::make_shared<MessageQueue<Microbe>>();
  _thread_ids = std::make_shared<MessageQueue<std::thread::id>>();
  _food = std::make_shared<Food>();
  _microbe_list = std::make_shared<MicrobeList>();
};

Evolution::~Evolution() {
    for (std::thread &t : _threads) {
        if (t.joinable()) {
          t.join();
        }
    }
}
  
void Evolution::_InitMicrobes() {
    std::uniform_int_distribution<int> disx = std::uniform_int_distribution<int>(0, _config_params->kGridWidth - 1);
    std::uniform_int_distribution<int> disy = std::uniform_int_distribution<int>(0, _config_params->kGridHeight - 1);
    std::uniform_int_distribution<int> disd = std::uniform_int_distribution<int>(0, 7);

   for (int i=0; i < _config_params->init_number_of_microbes; ++i) {

      _microbe_list->microbes.emplace_back(std::make_shared<Microbe>(disx(_gen), disy(_gen), 100, 
                                                       disd(_gen), _food, _config_params,
                                                      _new_microbes, _thread_ids));
   }

}

void Evolution::_InitFood() {
  //uniform
  std::vector<std::vector<bool>> arr;
  for (int y=0; y<_config_params->kGridHeight; ++y) {
    std::vector<bool> row;
    for (int x=0; x<_config_params->kGridWidth; ++x) {
      row.emplace_back(_disr(_gen)<_config_params->init_food_density);
    }
    arr.emplace_back(row);
  } 
  _food->values = std::move(arr);
}


void Evolution::_SpawnFoodUniform() {
    std::lock_guard<std::mutex> lock(_food->mx);
    for (int y=0; y<_config_params->kGridHeight; ++y) {
        for (int x=0; x<_config_params->kGridWidth; ++x) {
            if (_disr(_gen)<_config_params->spawn_food_density) {
                _food->values[y][x] = true;
            }
        }
    } 
}

void Evolution::_SpawnFoodLines() {
    std::lock_guard<std::mutex> lock(_food->mx);
    int d = _config_params->line_distance;
    for (int y=d/2; y<_config_params->kGridHeight; y+=d) {
        for (int x=0; x<_config_params->kGridWidth; ++x) {
            if (_disr(_gen)<_config_params->line_density) {
                _food->values[y][x] = true;
            }
        }
    } 
    for (int y=0; y<_config_params->kGridHeight; ++y) {
        for (int x=d/2; x<_config_params->kGridWidth; x+=d) {
            if (_disr(_gen)<_config_params->line_density) {
                _food->values[y][x] = true;
            }
        }
    }    
}

void Evolution::_SpawnFoodRectangle() {
    std::lock_guard<std::mutex> lock(_food->mx);
    int h = _config_params->kGridHeight;
    int w = _config_params->kGridWidth;
    for (int y=(h-_config_params->rect_h)/2; y<(h+_config_params->rect_h)/2; ++y) {
        for (int x=(w-_config_params->rect_w)/2; x<(w+_config_params->rect_w)/2; ++x) {
            if (_disr(_gen)<_config_params->rect_density) {
                _food->values[y][x] = true;
            }
        }
    } 
}

void Evolution::_SpawnFood() {
    while (!_config_params->finished) {
        std::this_thread::sleep_for(std::chrono::milliseconds(_config_params->kMsPerFoodSpawnCycle));
        FoodDistribution d = _config_params->food_distribution;
        switch (d) {
          case kLines: 
            _SpawnFoodLines();
            break;
          case kRectangle:
            _SpawnFoodRectangle();
            break;
          default:
            _SpawnFoodUniform();
        }
    }
};


void Evolution::_Add_New_Microbes() {

  while (!_config_params->finished) {
    std::shared_ptr<Microbe> microbe = std::make_shared<Microbe>(std::move(_new_microbes->receive()));
    if (!_config_params->finished) {
      {
          std::lock_guard<std::mutex> lock(_threads_mutex);
          _threads.emplace_back(std::thread(&Microbe::Live, microbe));
      }
      std::lock_guard<std::mutex> lock(_microbe_list->mx);
      _microbe_list->microbes.emplace_back(microbe);
    }
  }
}

void Evolution::_Cleanup() {
  int size;
  {
      std::lock_guard<std::mutex> lock(_microbe_list->mx);
      size = _microbe_list->microbes.size();
  }
  while (size > 0 && !_config_params->finished) {

    std::this_thread::sleep_for(std::chrono::milliseconds(_config_params->kMsPerCleanupCycle));
    std::lock_guard<std::mutex> lock(_microbe_list->mx);
    _microbe_list->microbes.erase(
        std::remove_if(_microbe_list->microbes.begin(), _microbe_list->microbes.end(),
            [](const auto m) { return m->IsDead(); }), 
        _microbe_list->microbes.end()   
    );
    size = _microbe_list->microbes.size();
  }
}

void Evolution::_CleanupThreads() {
  while (!_config_params->finished) {
    std::thread::id id = _thread_ids->receive();
    auto iter = std::find_if(_threads.begin(), _threads.end(), [=](std::thread &t) { return (t.get_id() == id); });
    if (iter != _threads.end())
    {
        iter->join();
        std::lock_guard<std::mutex> lock(_threads_mutex);
        _threads.erase(iter);
    }
  }
}

void Evolution::_Render(Controller const &controller, Renderer &renderer) {
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  std::vector<SDL_Rect> boxes {{10,5,30,20}, {50,5,30,20}, {90,5,30,20}};

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, _config_params, boxes);

    renderer.Render(_microbe_list, _food, boxes);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;


    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < _config_params->kMsPerFrame) {
      SDL_Delay(_config_params->kMsPerFrame - frame_duration);
    }
  }
  _config_params->finished = true; // should trigger termination of all threads
  _new_microbes->finish();
  _thread_ids->finish();
}


void Evolution::Run(Controller const &controller, Renderer &renderer) {
  
  _InitFood();
  _InitMicrobes();

  // start thread controller: wait for input
  // start thread for food: spawn new food every time step
  // start thread for microbes
  
  for(auto microbe : _microbe_list->microbes) {
    std::lock_guard<std::mutex> lock(_threads_mutex);
    _threads.emplace_back(std::thread(&Microbe::Live, microbe));
  }

  // start thread for adding new microbes
  std::thread tn(&Evolution::_Add_New_Microbes, this);
  
  // start thread for cleaning up the list lof microbes
  std::thread tc(&Evolution::_Cleanup, this);
  
  // start thread for cleaning up threads of dead microbes;
  std::thread tt(&Evolution::_CleanupThreads, this);
  
  // start thread for spawning food
  std::thread tf(&Evolution::_SpawnFood, this);
  
  // start Renderer, keep this in main thread
  _Render(controller, renderer);
  
  
  tf.join();
  tt.join();
  tc.join();
  tn.join();

};