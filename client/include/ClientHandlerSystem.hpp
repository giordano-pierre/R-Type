/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ClientHandlerSystem.hpp
*/

#pragma once

#include "ECS/ECS.hpp"
#include "ReceiveEvent.hpp"
#include "RequestEvent.hpp"

class ClientHandlerSystem {
  private:
    /* data */
  public:
    ClientHandlerSystem(){};
    ~ClientHandlerSystem(){};

    void operator()(ECS &ecs, const ReceiveEvent &rec_event);
};
