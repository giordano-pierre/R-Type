#pragma once

#include "ServerCore.hpp"
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

struct Position {
    float x = 0.0f;
    float y = 0.0f;

    Position(float px, float py) : x(px), y(py) {}
};

struct Velocity {
    float x = 0.0f;
    float y = 0.0f;
    bool active = true;

    Velocity(float px, float py, bool act) : x(px), y(py), active(false) {}
};

struct HitBox {
    float x = 0.0f;
    float y = 0.0f;
    float width = 0.0f;
    float height = 0.0f;

    HitBox(float px, float py, float wd, float ht)
        : x(px), y(py), width(wd), height(ht) {}
};

struct Health {
    int value = 100;
    int maxValue = 100;

    Health(int vl, int maxv) : value(vl), maxValue(maxv) {}
};

struct Damage {
    int value = 10;

    Damage(int vl) : value(vl) {}
};

struct PlayerData {
    std::string id;
    std::string name;
    Position pos;

    PlayerData(std::string id, std::string name) : id(id), name(name) {}
};

struct EnemyData {
    std::size_t lastDamageSource;
    int pointValue;

    EnemyData(std::size_t dam, int pVl)
        : lastDamageSource(dam), pointValue(pVl) {}
};

struct PlayerScore {
    int score{0};
    int kills{0};
    int deaths{0};
    float survivalTime{0.0f};

    PlayerScore() = default;

    PlayerScore(int score, int kills, int deaths, float surviTime)
        : score(0), kills(0), deaths(0), survivalTime(0.0) {}
};

struct EnemySpawn {
    float x;
    float y;
    float spawnTime;
    std::string type;
    int health;
    int pointValue;
    float speed;

    EnemySpawn(float px, float py, float spTime, std::string type, int health,
               int ptVl, float speed)
        : x(px), y(py), spawnTime(spTime), type(type), health(0), pointValue(0),
          speed(speed) {}
};

struct Level {
    std::vector<EnemySpawn> enemies;
    float duration;
    int minScoreToWin;

    Level() : duration(0.0f), minScoreToWin(0) {}

    Level(std::vector<EnemySpawn> enemies, float duration, int minScore)
        : enemies(enemies), duration(duration), minScoreToWin(minScore) {}
};

struct GameState {
    bool isGameRunning{false};
    float gameTime{0.0f};
    uint32_t playerCount{0};

    GameState(bool isRunning, float gameTime, uint32_t playerCount)
        : isGameRunning(false), gameTime(gameTime), playerCount(playerCount) {}
};

struct RefServer {
    Server &refToServer;

    RefServer(Server &_refToServer) : refToServer(_refToServer) {}
};
