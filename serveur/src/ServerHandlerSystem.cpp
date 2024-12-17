/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ServerHandlerSystem.cpp
*/

#include "ServerHandlerSystem.hpp"

#include <iostream>

void ServerHandlerSystem::operator()(ECS &ecs, const ReceiveEvent &rec_event)
{
    std::cout << "SERVER HANDLER" << std::endl;
    std::cout << "action : " << rec_event.action << std::endl;
    switch (rec_event.action)
    {
    case NetworkActions::NEW_CLIENT:
        ecs.post<RequestEvent>({NetworkActions::SEND_UUID, rec_event.payload, rec_event.sender_uuid});
        break;
    case NetworkActions::ENVOI_CLIENT: // example on how the switch case works
        std::cout << "RECU :" << std::endl;
        std::cout << rec_event.payload.dump() << std::endl;
        ecs.post<RequestEvent>({NetworkActions::ENVOI_SERV, {{"value", "bozo"}}, rec_event.sender_uuid});
    default:
        break;
    }
}
