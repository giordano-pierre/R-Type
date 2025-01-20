/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** RemoveSys
*/

#pragma once

#include "Components.hpp"
#include "ECS/ECS.hpp"
#include "Events.hpp"

namespace rtype::server {

class RemoveSys {
  public:
    RemoveSys() = default;
    ~RemoveSys() = default;

    void operator()(ECS &ecs, const RemoveClient &remove_event,
                    const SparseArray<Client> &clients);
};

} // namespace rtype::server
