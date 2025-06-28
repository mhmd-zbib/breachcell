#pragma once
#include <cstdint>
class HealthSystem
{
public:
  static HealthSystem &getInstance();
  void update();

private:
  HealthSystem();
  HealthSystem(const HealthSystem &) = delete;
  HealthSystem &operator=(const HealthSystem &) = delete;
};
