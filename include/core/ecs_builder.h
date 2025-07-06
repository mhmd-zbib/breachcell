#pragma once
#include "ecs/entity_manager.h"
#include "factories/enemy_factory.h"
#include "factories/player_factory.h"
#include "factories/wall_factory.h"
#include <memory>
class ECSBuilder {
public:
  static std::shared_ptr<EntityManager> build() {
    auto entityManager = std::make_shared<EntityManager>();
    auto playerFactory = std::make_shared<PlayerFactory>(entityManager);
    auto enemyFactory  = std::make_shared<EnemyFactory>(entityManager);
    auto wallFactory   = std::make_shared<WallFactory>(entityManager);
    entityManager->setPlayerFactory(playerFactory);
    entityManager->setEnemyFactory(enemyFactory);
    entityManager->setWallFactory(wallFactory);
    return entityManager;
  }
};
