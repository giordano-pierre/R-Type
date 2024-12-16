#pragma once

#include <cstddef>
#include <string>
#include <vector>

struct Position {
  float x = 0.0f;
  float y = 0.0f;
};

struct Velocity {
  float x = 0.0f;
  float y = 0.0f;
};

struct Health {
  int value = 100;
  int maxValue = 100;
};

struct Damage {
  int value = 10;
};

struct PlayerData {
  std::size_t id;
  std::string name;
};

struct EnemyData {
  std::size_t lastDamageSource;
  int pointValue;
};

struct PlayerScore {
  int score{0};
  int kills{0};
  int deaths{0};
  float survivalTime{0.0f};
};

struct EnemySpawn {
  float x;
  float y;
  float spawnTime;
  std::string type;
  int health;
  int pointValue;
  float speed;
};

struct Level {
  std::vector<EnemySpawn> enemies;
  float duration;
  int minScoreToWin;
};

struct GameState {
  bool isGameRunning{false};
  float gameTime{0.0f};
  uint32_t playerCount{0};
};