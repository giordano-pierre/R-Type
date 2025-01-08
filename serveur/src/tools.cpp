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
#include "systems/child/LifeSys.hpp"

namespace rtype::server {

void initSubECS(ECS &ecs, ECS &ecs_p, const std::string &id) {
    ecs.register_component<Tag>();
    ecs.register_component<Client>();
    ecs.register_component<PlayerData>();
    // ecs.register_component<Position>();
    // ecs.register_component<Velocity>();
    // ecs.register_component<HitBox>();
    // ecs.register_component<Score>();
    // ecs.register_component<Basics>();
    // ecs.register_component<Health>();

    ecs.register_event<TicEvent>();
    ecs.register_event<RemoveClient>();
    ecs.register_event<ReceiveEvent>();
    ecs.register_event<RequestEvent>();

    Entity link = ecs.spawn_entity();
    ecs.add_component<Tag>(link, {id});

    auto lifeSys = LifeSys();
    ecs.subscribe<RemoveClient, Client>(lifeSys);
}

} // namespace rtype::server
