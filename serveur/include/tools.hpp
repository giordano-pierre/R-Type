/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** tools
*/

#pragma once

#include "ECS/ECS.hpp"
#include "protocol.hpp"
#include <vector>

namespace rtype::server {

struct EnemyInfo {
    int x_pos;
    int y_pos;
    int x_velocity;
    int y_velocity;
    float x_hitbox;
    float y_hitbox;
    int health;
    int score;
    int spawn_tic;
    EntityType type;
};

enum StateGame {
    IN_GAME,
    IN_PAUSE,
    WAITING,
};

void initSubECS(ECS &ecs, ECS &ecs_p, const std::string &id);
void removeAll(ECS &ecs);
void loadSubSystem(ECS &ecs);
bool isEnemy(const EntityType &obj);

} // namespace rtype::server
