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
    case NetworkActions::ENVOI_CLIENT: // example on how the switch case works
        std::cout << "RECU :" << std::endl;
        std::cout << rec_event.payload.dump() << std::endl;
        ecs.post<RequestEvent>({NetworkActions::ENVOI_SERV,
                                {{"value", "bozo"}},
                                rec_event.sender_uuid});
    case NetworkActions::READY_SIGNAL:
        std::cout << "RECU :" << std::endl;
        std::cout << rec_event.payload.dump() << std::endl;
        ecs.post<RequestEvent>({NetworkActions::ENVOI_SERV,
                                {{"value", "bozo"}},
                                rec_event.sender_uuid});
    case NetworkActions::CLIENT_INPUT:
        auto input = rec_event.payload; 
        bool is_valid = true; // validate_input(input);
        json response = {{"action", input["action"]}};
        if (is_valid) {
            update_entity_state(input);
            response["status"] = "accepted";
        } else {
            response["status"] = "rollback";
        }

        ecs.post<RequestEvent>({
            NetworkActions::INPUT_RESPONSE,
            response,
            rec_event.sender_uuid
        });
    // case NetworkActions::CREATE_ENTITY: {
    //     json new_entity_data = {
    //         {"old_id", id_got_from_client_payload},
    //         {"id", generate_entity_id()},
    //         {"type", "enemy"},
    //         {"position", {100, 200}},
    //         {"velocity", {100, 200}},
    //         {"hitbox", {100, 200, 300, 500}},
    //         {"health", 100},
    //     };

    //     for (const auto &[uuid, endpoint] : clients_endpoint_) {
    //         ecs.post<RequestEvent>({
    //             NetworkActions::ENTITY_CREATED,
    //             new_entity_data,
    //             uuid
    //         });
    //     }
    // }
    // case NetworkActions::Update: {
    //     json new_entity_data = {
    //         {"id", generate_entity_id()},
    //         {"position", {100, 200}},
    //         {"velocity", {100, 200}}, (sauf player)
    //         {"health", 100},
    //     };

    //     for (const auto &[uuid, endpoint] : clients_endpoint_) {
    //         ecs.post<RequestEvent>({
    //             NetworkActions::ENTITY_CREATED,
    //             new_entity_data,
    //             uuid
    //         });
    //     }
    // }
    default:
        break;
    }
}
