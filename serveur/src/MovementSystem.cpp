/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MovementSystem.cpp
*/

#include "MovementSystem.hpp"
#include <iostream>

namespace rtype::server::systems {

auto MovementSys::operator()(ECS &ecs, const rtype::server::TicEvent &,
                             SparseArray<Position> &positions,
                             const SparseArray<Velocity> &velocities) -> void {
    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
        if (positions[i] && velocities[i] && velocities[i]->active) {
            positions[i]->x += velocities[i]->x;
            positions[i]->y += velocities[i]->y;
        }
    }
}

} // namespace systems
