/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** tools
*/

#pragma once

#include "Components.hpp"
#include "ECS/ECS.hpp"
#include "protocol.hpp"
#include <vector>

namespace rtype::server {

void removeAll(ECS &ecs);
bool isEnemy(const EntityType &obj);
void loadLevel(Stage &stage);

} // namespace rtype::server
