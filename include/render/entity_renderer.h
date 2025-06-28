#pragma once
class EntityRenderer
{
public:
  static EntityRenderer &getInstance();
  void render();

private:
  EntityRenderer() = default;
  EntityRenderer(const EntityRenderer &) = delete;
  EntityRenderer &operator=(const EntityRenderer &) = delete;
};
