/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CollisionSystem.hpp
*/

#pragma once
#include "ECS/ECS.hpp"
#include "Components.hpp"

namespace rtype {
    namespace systems {
        class CollisionSys {
            CollisionSys() = default;
            ~CollisionSys() = default;

            auto operator()(ECS &ecs,
                            SparseArray<Position> &positions,
                            const SparseArray<Hitbox> &hitboxes) -> bool;
            auto operator()(ECS &ecs,
                            SparseArray<Position> &positions) -> bool;
        };
    }
}