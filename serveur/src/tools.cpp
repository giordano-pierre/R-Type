/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** tools
*/

#include "tools.hpp"
#include "Components.hpp"
#include "Events.hpp"
#include "events/ReceiveEvent.hpp"
#include "events/RequestEvent.hpp"
#include <iostream>

namespace rtype::server {

void removeAll(ECS &ecs) {
    const auto &tags = ecs.get_components<Tag>();

    for (size_t i = 0; i < tags.size(); ++i) {
        const auto &tag = tags[i];

        if (tag && tag.value()._type != OTHER) {
            std::cout << "B KILL" << std::endl;
            ecs.kill_entity(ecs.entity_from_index(i));
            std::cout << "A KILL" << std::endl;
        }
    }
}

bool isEnemy(const EntityType &obj) {
    if (obj >= ENEMY1 && obj <= BOSS2)
        return true;
    return false;
}

} // namespace rtype::server
