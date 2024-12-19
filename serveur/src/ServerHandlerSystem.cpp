/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ServerHandlerSystem.cpp
*/

#include "ServerHandlerSystem.hpp"
#include <iostream>

void ServerHandlerSystem::operator()(ECS &ecs, const ReceiveEvent &rec_event) {
    std::cout << "SERVER HANDLER" << std::endl;
    std::cout << "action : " << rec_event.action << std::endl;
    switch (rec_event.action) {
    case NetworkActions::NEW_CLIENT:
        ecs.post<RequestEvent>({NetworkActions::SEND_UUID, rec_event.payload,
                                rec_event.sender_uuid});
        break;
    case NetworkActions::CLIENT_READY:
        std::cout << "RECU :" << std::endl;
        std::cout << rec_event.payload << std::endl;
        Entity newPlayer = ecs.spawn_entity();
        ecs.add_component<PlayerData>(newPlayer,
                                      {1, rec_event.payload.["name"]});
        // send CREATE_ENTITY to player
        break;
    case NetworkActions::SERVER_READY:
        ecs.post<RequestEvent>({NetworkActions::SEND_UUID, rec_event.payload,
                                rec_event.sender_uuid});
        break;
    case NetworkActions::CLIENT_CREATE:
        json new_entity_data = {
            {"tmp_id", rec_event.payload.["tmp_id"]},
            {"id", generate_entity_id()},
            {"type", rec_event.payload.["type"]},
            {"position", rec_event.payload.["position"]},
            {"velocity", rec_event.payload.["velocity"]},
            {"hitbox", rec_event.payload.["hitbox"]},
        };

        // ecs.post<RequestEvent>({
        //     NetworkActions::ENTITY_CREATED,
        //     new_entity_data,
        //     ""
        // });
        break;
    case NetworkActions::CREATE_ENTITY:
        // json new_entity_data = {
        //     {"id", generate_entity_id()},
        //     {"type", "enemy | player | shoot"},
        //     {"position", got from ecs},
        //     {"velocity", got from ecs},
        //     {"hitbox", got from ecs},
        //     {"health", got from ecs},
        // };

        // ecs.post<RequestEvent>({
        //     NetworkActions::ENTITY_CREATED,
        //     new_entity_data,
        //     ""
        // });
        break;
    case NetworkActions::UPDATE_ENTITY:
        // json new_entity_data = {
        //     {"id", generate_entity_id()},
        //     {"position", got from ecs},
        //     {"velocity", got from ecs},
        //     {"health", got from ecs},
        // };

        // ecs.post<RequestEvent>({
        //     NetworkActions::ENTITY_CREATED,
        //     new_entity_data,
        //     ""
        // });
        break;
    case NetworkActions::CLIENT_INPUT:
        auto input = rec_event.payload;
        bool is_valid = true; // validate_input(input);
        // if (is_valid)
        //     update_entity_state(input);
        break;
    case NetworkActions::CLIENT_DISCONNECT:
        std::cout << "RECU :" << std::endl;
        std::cout << rec_event.payload << std::endl;
        // remove player from player_list
        break;
    default:
        break;
    }
}