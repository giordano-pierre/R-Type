/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ServerHandlerSystem.hpp
*/

#pragma once

#include "Components.hpp"
#include "ECS/ECS.hpp"
#include "ReceiveEvent.hpp"
#include "RequestEvent.hpp"

class ServerHandlerSystem {
  private:
    /* data */
  public:
    ServerHandlerSystem() {};
    ~ServerHandlerSystem() {};

    void operator()(ECS &ecs, const ReceiveEvent &rec_event);
};

void serverReady(ECS &ecs);
void createEnemy(ECS &ecs,
                 rtype::server::EnemyInfo enemy);
void updateEntity(ECS &ecs);
void gameOver(ECS &ecs);