#pragma once

#include "Components.hpp"
#include "ECS/ECS.hpp"
#include "LevelManagement.hpp"
#include "ScoreManager.hpp"
#include <cstdint>
#include <vector>

namespace rtype::server {
namespace systems {

class GameLogicSystem {
  public:
    struct GameState {
        bool isGameRunning{false};
        float gameTime{0.0f};
        int playerCount{0};
    };

    explicit GameLogicSystem(ECS &ecs);
    ~GameLogicSystem() = default;
    GameState gameState;

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
} // namespace rtype::server