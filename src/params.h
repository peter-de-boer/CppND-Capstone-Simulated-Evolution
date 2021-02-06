#ifndef PARAMS_H
#define PARAMS_H

#include <vector>

enum FoodDistribution {
  kUniform,
  kLines,
  kRectangle
};

struct ConfigParams {
  int food_energy {40};
  int reproduce_energy {300};
  int timestep_energy {1};
  std::vector<int> change_direction_energy {0, 1, 2, 4, 8, 4, 2, 1};
  
  FoodDistribution food_distribution {kUniform};
  
  //uniform distribution params
  float init_food_density {0.1};
  float spawn_food_density {0.001};
  //line distribution params
  int line_distance {60};
  float line_density {0.1};
  //rectangle distributon params
  int rect_w {160};
  int rect_h {120};
  float rect_density {0.01};
  
  int init_number_of_microbes {200};

  //const int kFramesPerSecond{60};
  const int kMsPerFrame{50};
  const int kMsPerCleanupCycle{1000};
  const int kMsPerMicrobeCycle{10};
  const int kMsPerFoodSpawnCycle{100};
  const int kScreenWidth{1280};
  const int kScreenHeight{640};
  const int kGridWidth{640};
  const int kGridHeight{320};
  
  bool finished {false};
};

#endif