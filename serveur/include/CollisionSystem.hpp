/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CollisionSystem.hpp
*/

#pragma once
#include "Components.hpp"
#include "ECS/ECS.hpp"

namespace rtype {
namespace systems {
class CollisionSys {
  public:
    CollisionSys() = default;
    ~CollisionSys() = default;

    auto operator()(ECS &ecs, SparseArray<Position> &positions,
                    const SparseArray<HitBox> &hitboxes) -> bool;
    auto operator()(ECS &ecs, SparseArray<Position> &positions) -> bool;
};
} // namespace systems
} // namespace rtype