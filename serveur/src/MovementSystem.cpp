/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MovementSystem.cpp
*/

#include "MovementSystem.hpp"

namespace rtype {
    namespace systems {

        auto MovementSys::operator()(ECS &ecs,
                            SparseArray<Position> &positions,
                            const SparseArray<Velocity> &velocities) -> void
        {
            for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
                if (positions[i].has_value() && velocities[i].has_value() && velocities[i]->active) {
                    positions[i]->x += velocities[i]->x;
                    positions[i]->y += velocities[i]->y;
                }
            }
        }
    }
}