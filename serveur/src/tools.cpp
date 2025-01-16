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

    auto lifeSys = LifeSys();
    ecs.subscribe<RemoveClient, Client>(lifeSys);
    // ecs.subscribe<TicEvent, Dead>(lifeSys);
    return ecs;
}

void removeAll(std::shared_ptr<ECS> ecs) {
    const auto &tags = ecs.get()->get_components<Tag>();

    for (size_t i = 0; i < tags.size(); ++i) {
        const auto &tag = tags[i];

        if (tag && tag.value()._type != OTHER) {
            ecs.get()->kill_entity(ecs.get()->entity_from_index(i));
        }
    }
}

void loadSubSystem(std::shared_ptr<ECS> ecs) {
    // auto lifeSys = LifeSys();
    // ecs.subscribe<RemoveClient, Client>(lifeSys);
    // ecs.subscribe<TicEvent, Dead>(lifeSys);
    auto move = MovementSys();
    ecs.get()->subscribe<TicEvent, Position, Velocity>(move);
    auto life = HealthSys();
    ecs.get()->subscribe<TicEvent, Health>(life);
    auto coll = CollisionSys();
    ecs.get()->subscribe<TicEvent, Position, HitBox, Tag, Health, Owner, Score>(coll);
    ecs.get()->subscribe<TicEvent, Position, Tag, HitBox>(coll);
}

bool isEnemy(const EntityType &obj) {
    if (obj >= ENEMY1 && obj <= BOSS2)
        return true;
    return false;
}

} // namespace rtype::server
