/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MovementSystem.cpp
*/

#include "systems/child/MovementSystem.hpp"
#include <iostream>

namespace rtype::server {

auto MovementSys::operator()(ECS &ecs, const rtype::server::TicEvent &,
                             SparseArray<Position> &positions,
                             const SparseArray<Velocity> &velocities) -> void {
    // std::cout << "MOVE" << std::endl;
    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
        if (positions[i] && velocities[i] && velocities[i]->active) {
            positions[i]->x += velocities[i]->x;
            positions[i]->y += velocities[i]->y;
        }
    }
    // std::cout << "FINNNNN MOVE" << std::endl;
}

} // namespace rtype::server
