#pragma once
class AimingRenderer
{
public:
  static AimingRenderer &getInstance();
  void render();

private:
  AimingRenderer() = default;
  AimingRenderer(const AimingRenderer &) = delete;
  AimingRenderer &operator=(const AimingRenderer &) = delete;
};
