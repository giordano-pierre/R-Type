/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MoveSys
*/

#pragma once

#include "ECS/ECS.hpp"
#include "components/Drawable.hpp"
#include "components/Playable.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Tag.hpp"
#include "events/InputEvent.hpp"
#include "events/TicEvent.hpp"

namespace rtype::client {
class MoveSys {
  public:
    MoveSys() = default;
    ~MoveSys() = default;

    void operator()(ECS &ecs, const InputEvent &e_input,
                    const SparseArray<Playable> &players,
                    SparseArray<Velocity> &velocities);

    void operator()(ECS &ecs, const TicEvent &e_tic,
                    SparseArray<Position> &positions,
                    const SparseArray<Velocity> &velocities,
                    const SparseArray<Playable> &players,
                    const SparseArray<Tag> &tags);
};
} // namespace rtype::client
