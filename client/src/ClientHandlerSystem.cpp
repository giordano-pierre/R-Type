/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ClientHandlerSystem.cpp
*/

#include "ClientHandlerSystem.hpp"

#include <iostream>

void ClientHandlerSystem::operator()(ECS &ecs, const ReceiveEvent &rec_event) {
    std::cout << "Client HANDLER" << std::endl;
    std::cout << "action : " << rec_event.action << std::endl;
    switch (rec_event.action) {
    case NetworkActions::ENVOI_SERV:
        std::cout << "RECU :" << std::endl;
        std::cout << rec_event.payload.dump() << std::endl;
    default:
        break;
    }
}
