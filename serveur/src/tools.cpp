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
#include "systems/child/CollisionSystem.hpp"
#include "systems/child/HealthSystem.hpp"
#include "systems/child/LifeSys.hpp"
#include "systems/child/MovementSystem.hpp"
#include "systems/child/SubMessageHandlerSys.hpp"

namespace rtype::server {

void initSubECS(ECS &ecs, ECS &ecs_p, const std::string &id) {
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
    ecs.register_event<ReceiveEvent>();
    ecs.register_event<RequestEvent>();

    Entity link = ecs.spawn_entity();
    ecs.add_component<Tag>(link, {id});

    auto lifeSys = LifeSys();
    ecs.subscribe<RemoveClient, Client>(lifeSys);

    auto handler = SubMessageHandlerSys();
    ecs.subscribe<ReceiveEvent, Tag, Velocity>(handler);
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

void loadSubSystem(ECS &ecs) {
    auto move = MovementSys();
    ecs.subscribe<TicEvent, Position, Velocity>(move);
    auto life = HealthSys();
    ecs.subscribe<TicEvent, Health>(life);
    auto coll = CollisionSys();
    ecs.subscribe<TicEvent, Position, HitBox, Tag, Health, Owner, Score>(coll);
    ecs.subscribe<TicEvent, Position, Tag, HitBox>(coll);
}

bool isEnemy(const EntityType &obj) {
    if (obj >= ENEMY1 && obj <= BOSS2)
        return true;
    return false;
}

} // namespace rtype::server
