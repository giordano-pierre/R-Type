#pragma once

#include "enums.hpp"
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace timer = std::chrono;

namespace rtype::server {
struct Position {
    int x = 0;
    int y = 0;
    int initialX = 0;
    int initialY = 0;
    Position(int px, int py) : x(px), y(py), initialX(px), initialY(py){};
};

struct Velocity {
    int x = 0;
    int y = 0;
    int initialX = 0;
    int initialY = 0;
    bool active;

    Velocity(int px, int py, bool act = true)
        : x(px), y(py), initialX(px), initialY(py), active(act){};
};

struct HitBox {
    float x = 0.0f;
    float y = 0.0f;
    float width = 0.0f;
    float height = 0.0f;

    HitBox(float px, float py) : x(px), y(py) {
        width = {1920 * x};
        height = {1080 * y};
    };
};

struct Tag {
    std::string id;
    EntityType type;

    Tag(std::string id, EntityType type) : id(id), type(type){};
};

struct EnemyInfo {
    int x_pos;
    int y_pos;
    int x_velocity;
    int y_velocity;
    float x_hitbox;
    float y_hitbox;
    int health;
    int score;
};

struct Basics {
    std::vector<EnemyInfo> enemies1;
    std::map<std::string, bool> clientInGame;
    int minPlayer = -1;
    int nbPlayer = 0;
    int nbPlayerAlive = -1;
    int level = 0;
    int minScore = 100;
    bool gameState = false;
    Basics(std::vector<EnemyInfo> _enemies1) : enemies1(_enemies1){};
};

struct TicEvent {
    TicEvent(const timer::time_point<timer::steady_clock> &time_stamp)
        : time_stamp(time_stamp){};
    ~TicEvent() = default;

    timer::time_point<timer::steady_clock> time_stamp;
};

struct Health {
    int health = 100;
    int healthMax = 100;
    int HealthMin = 0;

    Health() = default;
};

struct PlayerData {
    std::size_t id;
    std::string name;

    PlayerData(std::string _name, std::size_t _id = 0) : id(_id), name(_name){};
};

struct Score {
    int score;

    Score(int score = 0) : score(score){};
};

} // namespace rtype::server