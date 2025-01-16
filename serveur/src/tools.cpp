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

namespace rtype::server {

ECS initSubECS(const std::string &id) {
    ECS ecs;

    ecs.register_component<Tag>();
    ecs.register_component<Client>();
    ecs.register_component<PlayerData>();
    ecs.register_component<Position>();
    ecs.register_component<Velocity>();
    ecs.register_component<HitBox>();
    ecs.register_component<Score>();
    ecs.register_component<Health>();
    ecs.register_component<Dead>();
    ecs.register_component<Owner>();

    ecs.register_event<TicEvent>();
    ecs.register_event<RemoveClient>();

    Entity link = ecs.spawn_entity();
    ecs.add_component<Tag>(link, {id});
    return ecs;
}

void removeAll(ECS &ecs) {
    const auto &tags = ecs.get_components<Tag>();

    for (size_t i = 0; i < tags.size(); ++i) {
        const auto &tag = tags[i];

        if (tag && tag.value()._type != OTHER) {
            ecs.kill_entity(ecs.entity_from_index(i));
        }
    }
}

bool isEnemy(const EntityType &obj) {
    if (obj >= ENEMY1 && obj <= BOSS2)
        return true;
    return false;
}

} // namespace rtype::server
