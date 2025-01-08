/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** tools
*/

#pragma once

#include "ECS/ECS.hpp"
#include "enums.hpp"
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
};

enum StateGame {
    IN_GAME,
    IN_PAUSE,
    WAITING,
};

void initSubECS(ECS &ecs, ECS &ecs_p, const std::string &id);

} // namespace rtype::server