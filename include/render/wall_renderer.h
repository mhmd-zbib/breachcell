#pragma once
class WallRenderer
{
public:
  static WallRenderer& getInstance();
  void render();

private:
  WallRenderer() = default;
  WallRenderer(const WallRenderer&) = delete;
  WallRenderer& operator=(const WallRenderer&) = delete;
};
