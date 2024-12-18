/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** createEntities
*/

#pragma once

#include "ECS/ECS.hpp"

namespace Rtype::Client {
void createGameEntities(ECS &ecs);
void createMenuEntities(ECS &ecs);
void createConfigEntities(ECS &ecs);
void createConfigPlayer1Entites(ECS &ecs);
} // namespace Rtype::Client
