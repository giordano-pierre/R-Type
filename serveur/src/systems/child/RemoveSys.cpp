/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** RemoveSys
*/

#include "systems/child/RemoveSys.hpp"
#include <iostream>

namespace rtype::server {

void RemoveSys::operator()(ECS &ecs, const RemoveClient &remove_event,
                           const SparseArray<Client> &clients) {
    for (size_t i = 0; i < clients.size(); ++i) {
        const auto &cl = clients[i];

        if (cl && cl.value()._uuid == remove_event._uuid) {
            // std::cout << "JE Met Dead" << std::endl;
            ecs.add_component<Dead>(ecs.entity_from_index(i), {});
        }
    }
}

} // namespace rtype::server
