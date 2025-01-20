/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Child
*/

#include "Child.hpp"
#include "systems/child/Singleton.hpp"
#include "systems/child/SpawnQueue.hpp"

auto spawnQueue = SpawnQueue();
namespace rtype::server {

void initSubECS(ECS &ecs) {

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
    ecs.register_component<EnemyAI>();

    ecs.register_event<TicEvent>();
    ecs.register_event<RemoveClient>();
    ecs.register_event<ReceiveEvent>();
}

void loadSubSystem(Child &child) {
    child._ecs_child.subscribe<RemoveClient, Client>(child._removeSys);
    child._ecs_child.subscribe<ReceiveEvent, Tag, Velocity>(child._messHandler);
}

void loadSubGameSystem(Child &child) {
    child._ecs_child.subscribe<TicEvent, Position, Velocity>(child._moveSys);
    child._ecs_child.subscribe<TicEvent, Health>(child._hpSys);
    child._ecs_child
        .subscribe<TicEvent, Position, HitBox, Tag, Health, Owner, Score>(
            child._collSys);
    child._ecs_child.subscribe<TicEvent, Position, Tag, HitBox>(child._collSys);
    auto enemiesSys = Singleton<EnemiesSys>();
    child._ecs_child.subscribe<TicEvent, Position, Tag, EnemyAI, Velocity>(
        enemiesSys.getInstance());

    spawnQueue.add(EnemyAI::BehaviorType::BOSS);
}

} // namespace rtype::server
