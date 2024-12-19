#include "GameLogicSystem.hpp"
#include "iostream"
namespace rtype::server {
namespace systems {

GameLogicSystem::GameLogicSystem(ECS &ecs_ref)
    : ecs(ecs_ref), levelManager(ecs_ref), gameState{false, 0.0f, 0} {
    initializeComponents();
}

void GameLogicSystem::initializeComponents() {
    ecs.register_component<Position>();
    ecs.register_component<Velocity>();
    ecs.register_component<Health>();
    ecs.register_component<Damage>();
    ecs.register_component<PlayerData>();
    ecs.register_component<EnemyData>();
}

void GameLogicSystem::startGame() {
    gameState.isGameRunning = true;
    gameState.gameTime = 0.0f;
    levelManager.loadLevel(1);
}

void GameLogicSystem::pauseGame() { gameState.isGameRunning = false; }

void GameLogicSystem::endGame() { gameState.isGameRunning = false; }

void GameLogicSystem::update(float deltaTime) {
    if (!gameState.isGameRunning)
        return;

    gameState.gameTime += deltaTime;

    levelManager.update(deltaTime);
    updateEntities(deltaTime);
    checkCollisions();

    checkGameRules();
    updateScores();

    if (levelManager.isLevelComplete()) {
        if (levelManager.hasNextLevel()) {
            levelManager.nextLevel();
        } else {
            endGame();
        }
    }
}

void GameLogicSystem::updateEntities(float dt) {
    auto &positions = ecs.get_components<Position>();
    auto &velocities = ecs.get_components<Velocity>();

    for (size_t i = 0; i < positions.size(); ++i) {
        if (positions[i].has_value() && velocities[i].has_value()) {
            positions[i]->x += velocities[i]->x * dt;
            positions[i]->y += velocities[i]->y * dt;
        }
    }
}

void GameLogicSystem::checkCollisions() {
    auto &positions = ecs.get_components<Position>();
    auto &enemies = ecs.get_components<EnemyData>();
    auto &players = ecs.get_components<PlayerData>();

    for (size_t i = 0; i < positions.size(); ++i) {
        if (!positions[i].has_value())
            continue;

        for (size_t j = i + 1; j < positions.size(); ++j) {
            if (!positions[j].has_value())
                continue;

            float dx = positions[i]->x - positions[j]->x;
            float dy = positions[i]->y - positions[j]->y;
            if (dx * dx + dy * dy < 25.0f) {
                handleCollision(Entity(i), Entity(j));
            }
        }
    }
}

void GameLogicSystem::handleCollision(Entity entity1, Entity entity2) {
    auto &healths = ecs.get_components<Health>();

    if (healths[entity1].has_value()) {
        healths[entity1]->value -= 10;
        if (healths[entity1]->value <= 0) {
            if (ecs.get_components<PlayerData>()[entity1].has_value()) {
                handlePlayerDeath(entity1);
            } else if (ecs.get_components<EnemyData>()[entity1].has_value()) {
                handleEnemyDeath(entity1);
            }
        }
    }
}

void GameLogicSystem::handlePlayerDeath(Entity player) {
    auto &playerData = ecs.get_components<PlayerData>()[player];
    if (playerData.has_value()) {
        scoreManager.addDeath(player);
        gameState.playerCount--;
        ecs.kill_entity(player);
    }
}

void GameLogicSystem::handleEnemyDeath(Entity enemy) {
    auto &enemyData = ecs.get_components<EnemyData>()[enemy];
    if (enemyData.has_value()) {
        scoreManager.updateScore(Entity(enemyData->lastDamageSource),
                                 enemyData->pointValue);
        ecs.kill_entity(enemy);
    }
}

void GameLogicSystem::checkGameRules() {
    if (gameState.playerCount == 0) {
        endGame();
        return;
    }
}

void GameLogicSystem::updateScores() {
    auto players = ecs.get_components<PlayerData>();
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i].has_value()) {
            scoreManager.updateTimeBonus(Entity(i), gameState.gameTime);
        }
    }
}

} // namespace systems
} // namespace rtype::server