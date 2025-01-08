/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CollisionSystem.hpp
*/

#pragma once
#include "Components.hpp"
#include "Events.hpp"
#include "ECS/ECS.hpp"

namespace rtype::server::systems {
class CollisionSys {
  public:
    CollisionSys() = default;
    ~CollisionSys() = default;

    void operator()(ECS &ecs, const rtype::server::TicEvent &,
                    const SparseArray<Position> &positions,
                    const SparseArray<HitBox> &hitboxes,
                    const SparseArray<Tag> &tags, SparseArray<Health> &healths,
                    const SparseArray<PlayerData> &playersdata,
                    SparseArray<Score> &scores);

    void operator()(ECS &ecs, const rtype::server::TicEvent &,
                    SparseArray<Position> &positions,
                    const SparseArray<Tag> &tags,
                    const SparseArray<HitBox> &hitboxes);
};
} // namespace rtype::server::systems
