/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** MessageHandlerSys
*/

#pragma once

#include "ECS/ECS.hpp"
#include "events/ReceiveEvent.hpp"
#include "ecsObjects.hpp"

namespace rtype::client {

class MessageHandlerSys {
    public:
        MessageHandlerSys() = default;
        ~MessageHandlerSys() = default;

    void operator()(ECS &ecs, const ReceiveEvent &rec_event,
                    SparseArray<Window> &windows,
                    const SparseArray<Tag> &tags,
                    SparseArray<Position> &positions,
                    SparseArray<Velocity> &velocities,
                    SparseArray<Health> &healths,
                    SparseArray<Score> &scores,
                    SparseArray<LastUpdate> &lastups);
};

}
