/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ClientHandlerSystem.cpp
*/

#include "ClientHandlerSystem.hpp"
#include "tools.hpp"
#include "ecsObjects.hpp"

#include <iostream>

Entity getEntityByID(const ECS &ecs, const std::string &id)
{
    const auto &tags = ecs.get_components<rtype::client::Tag>();

    for (size_t i = 0; i < tags.size(); ++i) {
        const auto &tag = tags[i];

        if (tag && tag.value()._id == id)
            return Entity(i);
    }
    return Entity(-1);
}

void createEntity(ECS &ecs, const ReceiveEvent &rec_event)
{
    auto &myWindow = ecs.get_components<rtype::client::Window>()[0].value();
    Entity entity = ecs.spawn_entity();

    switch (from_json(rec_event.payload["type"])) {
        case EntityType::PLAYER:
            ecs.add_component<rtype::client::Tag>(entity, {rtype::client::PLAYER, rec_event.payload["id"]});
            ecs.add_component<rtype::client::Position>(entity, {rec_event.payload["pos"]["x"], rec_event.payload["pos"]["y"]});
            ecs.add_component<rtype::client::Velocity>(entity, {0, 0});
            ecs.add_component<rtype::client::Playable>(entity, {1});
            ecs.add_component<rtype::client::Hitbox>(entity, {{rec_event.payload["hitbox"]["x"], rec_event.payload["hitbox"]["y"]}});
            ecs.add_component<rtype::client::Drawable>(
                entity,
                {myWindow._myTextures.getTexture("assets/images/ship/red_ship.png"),
                {395, 250},
                {395, 250},
                1,
                1});
            // ecs.add_component<Health>(entity, {});
            break;
        case EntityType::ENEMY1:
            ecs.add_component<rtype::client::Tag>(entity, {rtype::client::ENEMY, rec_event.payload["id"]});
            ecs.add_component<rtype::client::Position>(entity, {rec_event.payload["pos"]["x"], rec_event.payload["pos"]["y"]});
            ecs.add_component<rtype::client::Velocity>(entity, {rec_event.payload["velocity"]["x"], rec_event.payload["velocity"]["y"]});
            ecs.add_component<rtype::client::Hitbox>(entity, {{rec_event.payload["hitbox"]["x"], rec_event.payload["hitbox"]["y"]}});
            ecs.add_component<rtype::client::Drawable>(
                entity,
                {myWindow._myTextures.getTexture("assets/images/ship/enemy_ship_1.png"),
                {2030, 1450},
                {290, 290},
                35,
                1});
            // ecs.add_component<Health>(entity, {});
            break;
        case EntityType::SHOT:
            ecs.add_component<rtype::client::Tag>(entity, {rtype::client::SHOT, rec_event.payload["id"]});
            ecs.add_component<rtype::client::Position>(entity, {rec_event.payload["pos"]["x"], rec_event.payload["pos"]["y"]});
            ecs.add_component<rtype::client::Velocity>(entity, {rec_event.payload["velocity"]["x"], rec_event.payload["velocity"]["y"]});
            ecs.add_component<rtype::client::Hitbox>(entity, {{rec_event.payload["hitbox"]["x"], rec_event.payload["hitbox"]["y"]}});
            ecs.add_component<rtype::client::Drawable>(
                entity, {myWindow._myTextures.getTexture(
                           "assets/images/shot/purple_shot.png"),
                       {251, 144},
                       {251, 144},
                       1,
                       2});
            break;
        default:
            return;
    }
}

void updateEntity(ECS &ecs, Entity entity, const ReceiveEvent &rec_event)
{
    auto &pos = ecs.get_components<rtype::client::Position>()[entity];
    // auto &health = ecs.get_components<Health>();

    if (pos) {
        pos.value()._server = {rec_event.payload["pos"]["x"], rec_event.payload["pos"]["y"]};
        pos.value()._needUpdate = true;
    }
    // if (health) {
    //     // update data
    // }
}

void ClientHandlerSystem::operator()(ECS &ecs, const ReceiveEvent &rec_event) {
    std::cout << "Client HANDLER" << std::endl;
    std::cout << "action : " << rec_event.action << std::endl;
    switch (rec_event.action) {
    case NetworkActions::SERVER_READY:
        ecs.post<rtype::client::DeleteEvent>({rtype::client::MENU});
        ecs.post<rtype::client::CreateEvent>({rtype::client::PLAYER});
    case NetworkActions::CREATE_ENTITY:
        if (rec_event.payload.contains("tmp_id")) {
            auto entity = getEntityByID(ecs, rec_event.payload["id"]);
            if (entity == -1)
                return;
            auto &tag = ecs.get_components<rtype::client::Tag>()[entity];
            tag.value()._id = rec_event.payload["tmp_id"];
            updateEntity(ecs, entity, rec_event);
        } else
            createEntity(ecs, rec_event);
        break;
    case NetworkActions::UPDATE_ENTITY:
        auto entity = getEntityByID(ecs, rec_event.payload["id"]);
            if (entity == -1)
                return;
            updateEntity(ecs, entity, rec_event);
        break;
    }
}
