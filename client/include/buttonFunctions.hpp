/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** buttonFunctions
*/

#pragma once

#include "ECS/ECS.hpp"

namespace Rtype::Client {
void select(ECS &ecs, Entity i);
void deselect(ECS &ecs, Entity i);
void press(ECS &ecs, Entity i);
void resize1920(ECS &ecs, Entity i);
void resize1440(ECS &ecs, Entity i);
void resize960(ECS &ecs, Entity i);
} // namespace Rtype::Client
