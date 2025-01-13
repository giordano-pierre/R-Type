/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** ResendEventSys
*/

#pragma once

#include "ECS/ECS.hpp"
#include "Components.hpp"
#include "Events.hpp"

namespace rtype::server {

class ResendEventSys {
    public:
        ResendEventSys() = default;
        ~ResendEventSys() = default;

    void operator()(ECS &ecs, const CheckEvent &check_event,
                    const SparseArray<Room> &rooms,
                    const SparseArray<Tag> &tags);

};

}
