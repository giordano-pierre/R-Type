/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ServerHandlerSystem.hpp
*/

#pragma once

#include "Components.hpp"
#include "ECS/ECS.hpp"
#include "events/ReceiveEvent.hpp"
#include "events/RequestEvent.hpp"

class ServerHandlerSystem {
  private:
    /* data */
  public:
    ServerHandlerSystem(){};
    ~ServerHandlerSystem(){};

    void operator()(ECS &ecs, const ReceiveEvent &rec_event);
};

// void serverReady(ECS &ecs, const std::string &uuid);
// void createEnemy(ECS &ecs, rtype::server::EnemyInfo enemy);
// void updateEntity(ECS &ecs);
// void gameOver(ECS &ecs);