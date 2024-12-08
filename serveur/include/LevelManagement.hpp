#pragma once
#include "ECS/ECS.hpp"
#include "Components.hpp"
#include <vector>

namespace rtype {
    namespace systems {

        class LevelManager {
        public:
            explicit LevelManager(ECS& ecs);
            ~LevelManager() = default;

            void loadLevel(size_t levelNumber);
            void update(float gameTime);
            bool isLevelComplete() const;
            bool hasNextLevel() const;
            void nextLevel();
            size_t getCurrentLevel() const;

            void spawnEnemy(const EnemySpawn& spawn);
            void checkEnemySpawns(float currentTime);
            float getLevelProgress() const;
            size_t getRemainingEnemies() const;

        private:
            ECS& ecs;
            std::vector<Level> levels;
            size_t currentLevel{ 0 };
            float levelTime{ 0.0f };
            std::vector<EnemySpawn> remainingSpawns;
            bool levelComplete{ false };

            void initializeLevels();
        };

    }
}