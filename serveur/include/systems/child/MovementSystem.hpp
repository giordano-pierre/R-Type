/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MovementSystem.hpp
*/

#pragma once
#include "Components.hpp"
#include "ECS/ECS.hpp"
#include "Events.hpp"

namespace rtype::server {
class MovementSys {
  public:
    MovementSys() = default;
    ~MovementSys() = default;

    auto operator()(ECS &ecs, const rtype::server::TicEvent &,
                    SparseArray<Position> &positions,
                    const SparseArray<Velocity> &velocities) -> void;
};
} // namespace rtype::server
