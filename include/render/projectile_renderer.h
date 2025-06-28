#pragma once
#include <cstdint>
class ProjectileRenderer
{
public:
  static ProjectileRenderer &getInstance();
  void render();

private:
  ProjectileRenderer() = default;
  ProjectileRenderer(const ProjectileRenderer &) = delete;
  ProjectileRenderer &operator=(const ProjectileRenderer &) = delete;
};
