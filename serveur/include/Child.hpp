/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Child
*/

#pragma once

#include "systems/child/CollisionSystem.hpp"
#include "systems/child/HealthSystem.hpp"
#include "systems/child/MovementSystem.hpp"
#include "systems/child/RemoveSys.hpp"
#include "systems/child/SubMessageHandlerSys.hpp"
#include "systems/child/EnemiesSystem.hpp"

namespace rtype::server {

struct Child {
    ECS _ecs_child;
    RemoveSys _removeSys;
    SubMessageHandlerSys _messHandler;
    MovementSys _moveSys;
    HealthSys _hpSys;
    CollisionSys _collSys;

    Child() = default;
};

void loadSubSystem(Child &child);
void loadSubGameSystem(Child &child);
void initSubECS(ECS &ecs);

} // namespace rtype::server
