/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** buttonFunctions
*/

#pragma once

#include "ECS/ECS.hpp"

namespace rtype::client {
void select(ECS &ecs, Entity i);
void deselect(ECS &ecs, Entity i);
void press(ECS &ecs, Entity i);
void resize1920(ECS &ecs, Entity i);
void resize1440(ECS &ecs, Entity i);
void resize960(ECS &ecs, Entity i);
void langFR(ECS &ecs, Entity i);
void langEN(ECS &ecs, Entity i);
void resetG(ECS &ecs, Entity i);
void resetP1(ECS &ecs, Entity i);
void resetP2(ECS &ecs, Entity i);
void swapColorblind(ECS &ecs, Entity i);
void selectOnePlayer(ECS &ecs, Entity);
void selectTwoPlayer(ECS &ecs, Entity);
void createRoom(ECS &ecs, Entity);
void joinRoom(ECS &ecs, Entity i);
// void startGame1P(ECS &ecs, Entity i);
// void startGame2P(ECS &ecs, Entity i);
// void startGameMP(ECS &ecs, Entity i);
} // namespace rtype::client
