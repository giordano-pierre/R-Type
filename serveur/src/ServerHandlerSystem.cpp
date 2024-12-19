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
    Server &server = ecs.get_components<Server>()[0].value();

    switch (rec_event.action) {
    case NetworkActions::NEW_CLIENT:
        ecs.post<RequestEvent>({NetworkActions::SEND_UUID, rec_event.payload,
                                rec_event.sender_uuid});
        break;

    case NetworkActions::CLIENT_READY:
        Entity newPlayer = ecs.spawn_entity();
        ecs.add_component<PlayerData>(newPlayer, {fetch_new_uuid(), "Player1"});
        server.gameLogicSystem.gameState.playerCount += 1;

        ecs.post<RequestEvent>({NetworkActions::CREATE_ENTITY,
                                {
                                    {"id", fetch_new_uuid()},
                                    {"type", to_json(EntityType::PLAYER)},
                                    {"pos", {{"x", 100}, {"y", 540}}},
                                    {"hitbox", {{"x", 0.1}, {"y", 0.12}}},
                                },
                                ""});
        break;

    // case NetworkActions::SERVER_READY:
    //     ecs.post<RequestEvent>({NetworkActions::SEND_UUID, rec_event.payload,
    //                             rec_event.sender_uuid});
    //     break;
    case NetworkActions::CLIENT_CREATE:
        ecs.post<RequestEvent>({NetworkActions::CREATE_ENTITY,
                                {
                                    {"tmp_id", rec_event.payload["tmp_id"]},
                                    {"id", fetch_new_uuid()},
                                    {"type", rec_event.payload["type"]},
                                    {"position", rec_event.payload["position"]},
                                    {"velocity", rec_event.payload["velocity"]},
                                    {"hitbox", rec_event.payload["hitbox"]},
                                },
                                ""});
        break;
        // case NetworkActions::CREATE_ENTITY:
        //     json new_entity_data = {
        //         {"id", fetch_new_uuid()},
        //         {"type", "enemy | player | shoot"},
        //         {"position", got from ecs},
        //         {"velocity", got from ecs},
        //         {"hitbox", got from ecs},
        //         {"health", got from ecs},
        //     };

        //     ecs.post<RequestEvent>({
        //         NetworkActions::ENTITY_CREATED,
        //         new_entity_data,
        //         ""
        //     });
        //     break;
        // case NetworkActions::UPDATE_ENTITY:
        // json new_entity_data = {
        //     {"id", fetch_new_uuid()},
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

        auto input = rec_event.payload["type_event"];
        Entity player;

        auto temp = ecs.get_components<PlayerData>();
        for (size_t i = 0; i < temp.size(); i++) {
            if (temp[i])
                if rec_event
                    .payload["id"] == temp[i] { player = i; }
        }
        switch (input) {
        case "Up":
            // check if up is possible

            break;
        case "Down":
            // check if down possible and update player pos
            break;
        case "Right":
            // check if right ossible and update player pos
            break;
        case "Left":
            // check if left possible and update player pos
            break;
        default:
            break;
        }
        break;
    case NetworkActions::CLIENT_DISCONNECT:
        std::cout << "RECU :" << std::endl;
        std::cout << rec_event.payload << std::endl;
        // remove player from player_list
        break;
    }
}