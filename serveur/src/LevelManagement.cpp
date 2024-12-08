#include "LevelManager.hpp"

namespace rtype {
    namespace systems {

        LevelManager::LevelManager(ECS& ecs_ref) : ecs(ecs_ref) {
            initializeLevels();
        }

        void LevelManager::initializeLevels() {
            Level level1;
            level1.duration = 60.0f;
            level1.minScoreToWin = 1000;
            level1.enemies = {
                {800.0f, 100.0f, 2.0f, "basic", 50, 100, -100.0f},
                {800.0f, 200.0f, 4.0f, "basic", 50, 100, -100.0f},
                {800.0f, 300.0f, 6.0f, "basic", 50, 100, -100.0f},
                {900.0f, 150.0f, 10.0f, "shooter", 100, 200, -80.0f}
            };
            levels.push_back(level1);

            Level level2;
            level2.duration = 90.0f;
            level2.minScoreToWin = 2000;
            level2.enemies = {
                {800.0f, 100.0f, 2.0f, "basic", 75, 150, -120.0f},
                {800.0f, 200.0f, 3.0f, "basic", 75, 150, -120.0f},
                {900.0f, 150.0f, 5.0f, "shooter", 125, 250, -100.0f},
                {1000.0f, 300.0f, 8.0f, "boss", 500, 1000, -50.0f}
            };
            levels.push_back(level2);
        }

        void LevelManager::loadLevel(size_t levelNumber) {
            if (levelNumber > 0 && levelNumber <= levels.size()) {
                currentLevel = levelNumber - 1;
                levelTime = 0.0f;
                levelComplete = false;
                remainingSpawns = levels[currentLevel].enemies;
            }
        }

        void LevelManager::update(float gameTime) {
            levelTime += gameTime;
            checkEnemySpawns(levelTime);

            if (levelTime >= levels[currentLevel].duration && getRemainingEnemies() == 0) {
                levelComplete = true;
            }
        }

        void LevelManager::checkEnemySpawns(float currentTime) {
            auto it = remainingSpawns.begin();
            while (it != remainingSpawns.end()) {
                if (currentTime >= it->spawnTime) {
                    spawnEnemy(*it);
                    it = remainingSpawns.erase(it);
                }
                else {
                    ++it;
                }
            }
        }

        void LevelManager::spawnEnemy(const EnemySpawn& spawn) {
            Entity enemy = ecs.spawn_entity();

            ecs.emplace_component<Position>(enemy, spawn.x, spawn.y);
            ecs.emplace_component<Velocity>(enemy, spawn.speed, 0.0f);
            ecs.emplace_component<Health>(enemy, spawn.health, spawn.health);
            ecs.emplace_component<EnemyData>(enemy, 0, spawn.pointValue);

            if (spawn.type == "shooter") {
                ecs.emplace_component<Damage>(enemy, 20);
            }
            else if (spawn.type == "boss") {
                ecs.emplace_component<Damage>(enemy, 50);
            }
        }

        bool LevelManager::isLevelComplete() const {
            return levelComplete;
        }

        bool LevelManager::hasNextLevel() const {
            return currentLevel + 1 < levels.size();
        }

        void LevelManager::nextLevel() {
            if (hasNextLevel()) {
                loadLevel(currentLevel + 2);
            }
        }

        size_t LevelManager::getCurrentLevel() const {
            return currentLevel + 1;
        }

        size_t LevelManager::getRemainingEnemies() const {
            size_t count = 0;
            auto& enemyComponents = ecs.get_components<EnemyData>();

            for (const auto& enemy : enemyComponents) {
                if (enemy.has_value()) {
                    count++;
                }
            }

            return count + remainingSpawns.size();
        }

        float LevelManager::getLevelProgress() const {
            return std::min(levelTime / levels[currentLevel].duration, 1.0f);
        }

    }
}