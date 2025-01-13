/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CollisionSystem.hpp
*/

#pragma once
#include "Components.hpp"
#include "ECS/ECS.hpp"
#include "Events.hpp"

namespace rtype::server {
class CollisionSys {
  public:
    CollisionSys() = default;
    ~CollisionSys() = default;

    void operator()(ECS &ecs, const TicEvent &,
                    const SparseArray<Position> &positions,
                    const SparseArray<HitBox> &hitboxes,
                    const SparseArray<Tag> &tags, SparseArray<Health> &healths,
                    const SparseArray<Owner> &owners,
                    SparseArray<Score> &scores);

    void operator()(ECS &ecs, const TicEvent &,
                    SparseArray<Position> &positions,
                    const SparseArray<Tag> &tags,
                    const SparseArray<HitBox> &hitboxes);
};
} // namespace rtype::server
