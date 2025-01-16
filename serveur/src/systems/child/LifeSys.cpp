/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** LifeSys
*/

#include "systems/child/LifeSys.hpp"
#include <iostream>

namespace rtype::server {

void LifeSys::operator()(ECS &ecs, const RemoveClient &remove_event,
                         const SparseArray<Client> &clients) {
    // std::cout << "LIFE" << std::endl;
    for (size_t i = 0; i < clients.size(); ++i) {
        const auto &cl = clients[i];

        if (cl && cl.value()._uuid == remove_event._uuid) {
            std::cout << "JE Met Dead" << std::endl;
            ecs.add_component<Dead>(ecs.entity_from_index(i), {});
        }
    }
    // std::cout << "FINNNNNNNNNNN LIFE" << std::endl;
}

void LifeSys::operator()(ECS &ecs, const TicEvent &,
                         const SparseArray<Dead> &deads) {
    // std::cout << "LIFE2" << std::endl;
    for (size_t i = 0; i < deads.size(); ++i) {
        const auto &dead = deads[i];

        if (dead && dead.value()._isDead)
            ecs.kill_entity(ecs.entity_from_index(i));
    }
    // std::cout << "FINNNNNNNNNNN LIFE2" << std::endl;
}

} // namespace rtype::server
