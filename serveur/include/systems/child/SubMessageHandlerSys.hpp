/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** SubMessageHandlerSys
*/

#pragma once

#include "Components.hpp"
#include "ECS/ECS.hpp"
#include "events/ReceiveEvent.hpp"

namespace rtype::server {

class SubMessageHandlerSys {
  public:
    SubMessageHandlerSys() = default;
    ~SubMessageHandlerSys() = default;

    void operator()(ECS &ecs, const ReceiveEvent &rec_event,
                    const SparseArray<Tag> &tags,
                    SparseArray<Velocity> &velocities);
};

} // namespace rtype::server
