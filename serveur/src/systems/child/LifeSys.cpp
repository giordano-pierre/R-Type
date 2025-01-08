/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** LifeSys
*/

#include "systems/child/LifeSys.hpp"

namespace rtype::server {

void LifeSys::operator()(ECS &ecs, const RemoveClient &remove_event,
                         const SparseArray<Client> &clients) {
    for (size_t i = 0; i < clients.size(); ++i) {
        const auto &cl = clients[i];

        if (cl && cl.value()._uuid == remove_event._uuid)
            ecs.kill_entity(ecs.entity_from_index(i));
    }
}

} // namespace rtype::server
