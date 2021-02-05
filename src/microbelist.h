#ifndef MICROBELIST_H
#define MICROBELIST_H

#include <mutex>
#include <vector>
#include "microbe.h"

struct MicrobeList {
  std::vector<std::shared_ptr<Microbe>> microbes;
  std::mutex mx;
};

#endif