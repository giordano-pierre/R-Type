/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** LifeSys
*/

#pragma once

#include "Components.hpp"
#include "ECS/ECS.hpp"
#include "Events.hpp"

namespace rtype::server {

class LifeSys {
  public:
    LifeSys() = default;
    ~LifeSys() = default;

    void operator()(ECS &ecs, const RemoveClient &remove_event,
                    const SparseArray<Client> &clients);
};

} // namespace rtype::server
