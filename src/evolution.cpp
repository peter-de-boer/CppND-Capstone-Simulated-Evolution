#include "evolution.h"
#include <algorithm>

#include <iostream>
#include <functional>
#include <future>

Evolution::Evolution(std::shared_ptr<ConfigParams> config_params) : _config_params(config_params) {
  _new_microbes = std::make_shared<MessageQueue<Microbe>>();
  _thread_ids = std::make_shared<MessageQueue<std::thread::id>>();
};

Evolution::~Evolution() {
    std::cout << "~Evolution\n";
    //std::for_each(_threads.begin(), _threads.end(), [](std::thread &t) {
    //    t.join();
    //});
    std::cout << "number of _threads: " << _threads.size() << "\n";
    for (std::thread &t : _threads) {
        if (t.joinable()) t.join();
    }
    std::cout << "end of ~Evolution\n";
}
  
void Evolution::_InitMicrobes() {
    std::uniform_int_distribution<int> disx = std::uniform_int_distribution<int>(0, _config_params->kGridWidth - 1);
    std::uniform_int_distribution<int> disy = std::uniform_int_distribution<int>(0, _config_params->kGridHeight - 1);
    std::uniform_int_distribution<int> disd = std::uniform_int_distribution<int>(0, 7);
   for (int i; i < _config_params->init_number_of_microbes; ++i) {
      _microbes.emplace_back(std::make_shared<Microbe>(disx(_gen), disy(_gen), 100, 
                                                       disd(_gen), _food, _config_params,
                                                      _new_microbes));
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
  _food = std::make_shared<std::vector<std::vector<bool>>>(std::move(arr));
}

void Evolution::_Add_New_Microbes() {
  while (!_config_params->finished) {
    std::shared_ptr<Microbe> microbe = std::make_shared<Microbe>(std::move(_new_microbes->receive()));
    if (!_config_params->finished) {
      _threads.emplace_back(std::thread(&Microbe::Live, microbe));
      _microbes.emplace_back(microbe);
    }
  }
}

void Evolution::_Cleanup() {
  while (_microbes.size() > 0 && !_config_params->finished) {

    std::this_thread::sleep_for(std::chrono::milliseconds(_config_params->kMsPerCleanupCycle));
    _microbes.erase(
        std::remove_if(_microbes.begin(), _microbes.end(),
            [](const auto m) { return m->IsDead(); }), 
        _microbes.end()   
    );
  }
}

void Evolution::_CleanupThreads() {
  while (!_config_params->finished) {
    std::cout << "before _thread_ids->receive()\n";
    std::thread::id id = _thread_ids->receive();
    std::cout << "after _thread_ids->receive()\n";
    auto iter = std::find_if(_threads.begin(), _threads.end(), [=](std::thread &t) { return (t.get_id() == id); });
    if (iter != _threads.end())
    {
        iter->join();
        _threads.erase(iter);
    }
  }
}

void Evolution::_Render(Controller const &controller, Renderer &renderer) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running);

    renderer.Render(_microbes, _food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    /*
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }
    */

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < _config_params->kMsPerFrame) {
      SDL_Delay(_config_params->kMsPerFrame - frame_duration);
    }
  }
  std::cout << "Trigger finish\n";
  _config_params->finished = true; // should trigger termination of all threads
  _new_microbes->finish();
  _thread_ids->finish();
  std::cout << "End of Trigger finish\n";
}


void Evolution::Run(Controller const &controller, Renderer &renderer) {
  
  _InitFood();
  _InitMicrobes();

  // start thread controller: wait for input
  // start thread for food: spawn new food every time step
  // start thread for microbes
  std::lock_guard<std::mutex> lock(threadMutex);
  std::cout << "before adding microbes, number of _threads: " << _threads.size() << "\n";
  for(auto microbe : _microbes) {
    _threads.emplace_back(std::thread(&Microbe::Live, microbe));
    // might need to use futures in order to check if threads are finished so 
    // they can be cleaned up
  }
  std::cout << "after adding microbes, number of _threads: " << _threads.size() << "\n";

  // start thread for adding new microbes
  std::thread tn(&Evolution::_Add_New_Microbes, this);
  
  // start thread for cleaning up the list lof microbes
  std::thread tc(&Evolution::_Cleanup, this);
  
  // start thread for cleaning up threads of dead microbes;
  std::thread tt(&Evolution::_CleanupThreads, this);
  
  // start thread for Renderer: update screen after each time step
  std::thread tr(&Evolution::_Render, this, std::ref(controller), std::ref(renderer));
  
  std::cout << "before tr.join()\n";
  tr.join();
  std::cout << "before tt.join()\n";
  tt.join();
  std::cout << "before tc.join()\n";
  tc.join();
  std::cout << "before tn.join()\n";
  tn.join();
  std::cout << "after tn.join()\n";
  
  

  
};