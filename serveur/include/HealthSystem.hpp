/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** HealthSystem.hpp
*/

#pragma once
#include "Components.hpp"
#include "ECS/ECS.hpp"

namespace rtype::server::systems {
class HealthSys {
  public:
    HealthSys() = default;
    ~HealthSys() = default;

    void operator()(ECS &ecs, const rtype::server::TicEvent &,
                    const SparseArray<Health> &healths,
                    SparseArray<Basics> &basics);
};
} // namespace rtype::server::systems
