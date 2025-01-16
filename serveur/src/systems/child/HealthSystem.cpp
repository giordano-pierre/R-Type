/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** HealthSystem.cpp
*/

#include "systems/child/HealthSystem.hpp"
#include <iostream>

namespace rtype::server {

void HealthSys::operator()(ECS &ecs, const TicEvent &,
                           const SparseArray<Health> &healths) {
    // std::cout << "HEALTH" << std::endl;
    for (size_t i = 0; i < healths.size(); ++i) {
        const auto &health = healths[i];

        if (health && health.value()._health <= 0) {
            ecs.add_component<Dead>(ecs.entity_from_index(i), {});
        }
    }
    // std::cout << "FINNNNN HEALTH" << std::endl;
}

} // namespace rtype::server
