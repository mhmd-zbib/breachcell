#pragma once
#include <cstdint>

class IAimingSystem {
public:
  virtual ~IAimingSystem()                          = default;
  virtual void update(std::uint32_t playerEntityId) = 0;
};

class EntityManager;
class CameraService;
class InputHandler;

class AimingSystem : public IAimingSystem {
public:
  AimingSystem();
  void  update(std::uint32_t playerEntityId) override;
  void  update(std::uint32_t playerEntityId, float mousePositionX, float mousePositionY);
  void  update(std::uint32_t playerEntityId, float mousePositionX, float mousePositionY,
               EntityManager* entityManager, CameraService* cameraService,
               InputHandler* inputHandler);
  void  update(std::uint32_t playerEntityId, EntityManager* entityManager,
               CameraService* cameraService, InputHandler* inputHandler);
  void  triggerPostShotConeExpansion(std::uint32_t playerEntityId);
  void  triggerPostShotConeExpansion(std::uint32_t playerEntityId, EntityManager* entityManager);
  float getAimAngle() const;
  float getAimConeHalfAngle() const;
  float getShootConeHalfAngle(std::uint32_t playerEntityId) const;
  float getShootConeHalfAngle(std::uint32_t playerEntityId, EntityManager* entityManager) const;

private:
  float                  aimAngle                      = 0.0f;
  float                  aimConeHalfAngle              = 0.0f;
  bool                   isShooting                    = false;
  float                  standingStillTime             = 0.0f;
  float                  lastVelocityMagnitude         = 0.0f;
  float                  lastUpdateTime                = 0.0f;
  float                  currentConeDegrees            = 0.0f;
  float                  targetConeDegrees             = 0.0f;
  static constexpr float STANDING_CONE_DEGREES         = 6.0f;
  static constexpr float STANDING_FOCUSED_CONE_DEGREES = 2.0f;
  static constexpr float SLOW_WALK_CONE_DEGREES        = 10.0f;
  static constexpr float WALKING_CONE_DEGREES          = 18.0f;
  static constexpr float STANDING_SHOOT_CONE_DEGREES   = 8.0f;
  static constexpr float SLOW_WALK_SHOOT_CONE_DEGREES  = 14.0f;
  static constexpr float WALKING_SHOOT_CONE_DEGREES    = 24.0f;
  static constexpr float coneTransitionSpeed           = 40.0f;
};
