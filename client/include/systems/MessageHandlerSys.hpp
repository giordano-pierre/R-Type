/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** MessageHandlerSys
*/

#pragma once

#include "ECS/ECS.hpp"
#include "ecsObjects.hpp"
#include "events/ReceiveEvent.hpp"

namespace rtype::client {

class MessageHandlerSys {
  public:
    MessageHandlerSys() = default;
    ~MessageHandlerSys() = default;

    void operator()(ECS &ecs, const ReceiveEvent &rec_event,
                    SparseArray<Room> &rooms,
                    SparseArray<SFMLObjects> &SFMLObjs,
                    const SparseArray<Tag> &tags,
                    SparseArray<Position> &positions,
                    SparseArray<Velocity> &velocities,
                    SparseArray<Health> &healths,
                    SparseArray<Score> &scores,
                    SparseArray<LastUpdate> &lastups);
};

} // namespace rtype::client
