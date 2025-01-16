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

namespace rtype::server {

struct Child {
    ECS _ecs_child;
    RemoveSys _removeSys;
    MovementSys _moveSys;
    HealthSys _hpSys;
    CollisionSys _collSys;

    Child(const std::string &id) : _ecs_child(initSubECS(id)) {
        _ecs_child.subscribe<RemoveClient, Client>(_removeSys, true);
    };
};

void loadSubSystem(Child &child);

} // namespace rtype::server
