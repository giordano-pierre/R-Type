/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** HealthSystem.cpp
*/

#include "HealthSystem.hpp"
#include "ServerHandlerSystem.hpp"

namespace rtype::server::systems {

void rtype::server::systems::HealthSys::operator()(
    ECS &ecs, const rtype::server::TicEvent &,
    const SparseArray<Health> &healths, SparseArray<Basics> &basics) {

    for (size_t i = 0; i < healths.size(); ++i) {

        const auto health = healths[i];
        if (!health)
            continue;

        if (health.value().health <= 0) {
            basics[0].value().nbPlayerAlive -= 1;
            ecs.kill_entity(Entity(i));
            gameOver(ecs);
        }
    }
}

} // namespace systems
