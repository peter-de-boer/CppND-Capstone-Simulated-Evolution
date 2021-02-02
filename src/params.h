#ifndef PARAMS_H
#define PARAMS_H

#include <vector>

enum FoodDistribution {
  kUniform,
  kLines,
  kRectangles,
  tMixed
};

struct ConfigParams {
  int food_energy {40};
  int max_energy {1500};
  int reproduce_energy {1000};
  int timestep_energy {1};
  std::vector<int> change_direction_energy {0, 1, 2, 4, 8, 4, 2, 1};
  
  float init_food_density {0.2};
  float spawn_food_density {0.1};

  const int kFramesPerSecond{60};
  const int kMsPerFrame{15};
  const int kMsPerCleanupCycle{1000};
  const int kMsPerMicrobeCycle{100};
  const int kMsPerFoodSpawnCycle{100};
  const std::size_t kScreenWidth{640};
  const std::size_t kScreenHeight{320};
  const std::size_t kGridWidth{80};
  const std::size_t kGridHeight{40};
  
  bool finished {false};
};

#endif