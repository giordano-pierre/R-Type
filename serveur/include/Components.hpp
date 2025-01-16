/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Components
*/

#pragma once

#include "ECS/ECS.hpp"
#include "protocol.hpp"
#include "tools.hpp"
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace rtype::server {

struct Tag {
    std::string _id;
    EntityType _type;

    Tag(std::string id, EntityType type = OTHER) : _id(id), _type(type){};
};

struct Room {
    std::string _name;
    std::string _master;
    std::map<std::string, std::pair<StateGame, int>> _clients_uuid;
    int _lastUpdate;
    StateGame _state = WAITING;

    Room(std::string name, std::string master, int nbPlayer)
        : _name(name), _master(master) {
        _clients_uuid.insert({master, {WAITING, nbPlayer}});
        _lastUpdate = 0;
    }
};

struct Child {
    std::shared_ptr<ECS> _ecs_child;

    Child(const std::string &id)
        : _ecs_child(std::make_shared<ECS>(initSubECS(id))){};
};

struct Stage {
    int _nb;
    std::string _mapFile;
    std::vector<EnemyInfo> _enemies;

    Stage(int nb) : _nb(nb), _mapFile("stage_" + std::to_string(nb) + ".json") {
        std::vector<EnemyInfo> enemies = {
            {2000, 500, -9, 0, 0.1, 0.18, 100, 60, 0, ENEMY1},
            {2000, 1000, -8, 0, 0.1, 0.18, 100, 30, 100, ENEMY1},
            {2000, 800, -7, 0, 0.1, 0.18, 100, 50, 100, ENEMY1},
            {2000, 100, -10, 0, 0.1, 0.18, 100, 40, 200, ENEMY1}};
        // à créer en fonction du fichier
        _enemies = enemies;
    }
};

struct Client {
    std::string _uuid;

    Client(std::string uuid) : _uuid(uuid) {}
};

struct PlayerData {
    std::string _name;
    std::string _color;

    PlayerData(std::string name, std::string color)
        : _color(color), _name(name){};
};

struct Position {
    float x = 0;
    float y = 0;
    // float initialX = 0;
    // float initialY = 0;
    Position(float px, float py) : x(px), y(py){};
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
    float x;
    float y;
    float width;
    float height;

    HitBox(float px, float py) : x(px), y(py) {
        width = {1920 * x};
        height = {1080 * y};
    };
};

struct Health {
    int _health;

    Health(int health = 10) : _health(health){};
};

struct Dead {
    bool _isDead;

    Dead(void) : _isDead(true) {}
};

struct Score {
    int _score;

    Score(int score = 0) : _score(score){};
};

struct Owner {
    std::string _id_owner;
};

// struct Basics {
//     std::vector<EnemyInfo> enemies1;
//     std::map<std::string, bool> clientInGame;
//     int minPlayer = -1;
//     int nbPlayer = 0;
//     int nbPlayerAlive = -1;
//     int level = 0;
//     int minScore = 100;
//     bool gameState = false;
//     Basics(std::vector<EnemyInfo> _enemies1) : enemies1(_enemies1){};
// };

} // namespace rtype::server