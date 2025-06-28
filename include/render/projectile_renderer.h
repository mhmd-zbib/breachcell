#pragma once
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
