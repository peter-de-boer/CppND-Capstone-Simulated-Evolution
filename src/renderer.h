#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include "params.h"

class Renderer {
 public:
  Renderer(std::shared_ptr<ConfigParams> config_params);
  ~Renderer();

 private:

};

#endif