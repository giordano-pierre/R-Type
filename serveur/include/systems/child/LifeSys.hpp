/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** LifeSys
*/

#pragma once

#include "ECS/ECS.hpp"
#include "Events.hpp"
#include "Components.hpp"

namespace rtype::server {

class LifeSys {
    public:
        LifeSys() = default;
        ~LifeSys() = default;

    void operator()(ECS &ecs, const RemoveClient &remove_event,
                    const SparseArray<Client> &clients);
};

}
