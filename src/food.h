#ifndef FOOD_H
#define FOOD_H

#include <mutex>
#include <vector>

struct Food {
  std::vector<std::vector<bool>> values;
  std::mutex mx;
};

#endif