#pragma once

#include "Components.hpp"
#include "ECS/ECS.hpp"
#include "LevelManager.hpp"
#include "ScoreManager.hpp"
#include <cstdint>

namespace rtype {
namespace systems {

class GameLogicSystem {
public:
  struct GameState {
    bool isGameRunning{false};
    float gameTime{0.0f};
    uint32_t playerCount{0};
  };

  explicit GameLogicSystem(ECS &ecs);
  ~GameLogicSystem() = default;

  void update(float deltaTime);
  void startGame();
  void pauseGame();
  void endGame();

  bool isGameRunning() const { return gameState.isGameRunning; }
  float getGameTime() const { return gameState.gameTime; }
  uint32_t getPlayerCount() const { return gameState.playerCount; }

private:
  ECS &ecs;
  LevelManager levelManager;
  ScoreManager scoreManager;
  GameState gameState;

  void initializeComponents();
  void updateEntities(float dt);
  void checkCollisions();
  void handleCollision(Entity entity1, Entity entity2);
  void handlePlayerDeath(Entity player);
  void handleEnemyDeath(Entity enemy);
  void checkGameRules();
  void updateScores();
};

} // namespace systems
} // namespace rtype