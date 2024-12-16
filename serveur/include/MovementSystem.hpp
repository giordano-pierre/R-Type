/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MovementSystem.hpp
*/

#pragma once
#include "ECS/ECS.hpp"
#include "Components.hpp"

namespace rtype {
    namespace systems {
        class MovementSys {
            MovementSys() = default;
            ~MovementSys() = default;

            auto operator()(ECS &ecs,
                            SparseArray<Position> &positions,
                            const SparseArray<Velocity> &velocities) -> void;
        };
    }
}