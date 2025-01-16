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
#include "UDPServer.hpp"

class ServerHandlerSystem {
  private:
    /* data */
  public:
    ServerHandlerSystem(){};
    ~ServerHandlerSystem(){};

    void operator()(ECS &ecs, const ReceiveEvent &rec_event);
};

void serverReady(ECS &ecs, const std::string &uuid);
void createEnemy(ECS &ecs, rtype::server::EnemyInfo enemy);
void updateEntity(ECS &ecs);
void gameOver(ECS &ecs);
void createEnemy(ECS &ecs, rtype::server::EnemyInfo enemy);
void createEnemyWithAI(ECS &ecs, rtype::server::EnemyInfo enemyInfo,
                       rtype::server::EnemyAI::BehaviorType behavior);
void serverReady(ECS &ecs, const std::string &uuid);
void gameOver(ECS &ecs);
void updateEntity(ECS &ecs);