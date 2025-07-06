#pragma once
#include "core/engine.h"
#include <memory>
#include <string>

class GameFacade {
public:
  explicit GameFacade(std::shared_ptr<Engine> engineInstance, const std::string& windowTitle,
                      int windowWidth, int windowHeight);
  int start();

private:
  std::shared_ptr<Engine> engine;
  std::string             title;
  int                     width;
  int                     height;
};
