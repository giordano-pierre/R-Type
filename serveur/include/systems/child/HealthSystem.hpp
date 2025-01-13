/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** HealthSystem.hpp
*/

#pragma once
#include "Components.hpp"
#include "ECS/ECS.hpp"
#include "Events.hpp"

namespace rtype::server {
class HealthSys {
  public:
    HealthSys() = default;
    ~HealthSys() = default;

    void operator()(ECS &ecs, const TicEvent &,
                    const SparseArray<Health> &healths);
};
} // namespace rtype::server::systems
