/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ServerHandlerSystem.hpp
*/

#pragma once

#include "ECS/ECS.hpp"
#include "ReceiveEvent.hpp"
#include "RequestEvent.hpp"

class ServerHandlerSystem {
  private:
    /* data */
  public:
    ServerHandlerSystem(){};
    ~ServerHandlerSystem(){};

    void operator()(ECS &ecs, const ReceiveEvent &rec_event);
};
