/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** createEntities
*/

#pragma once

#include "ECS/ECS.hpp"

namespace rtype::client {
void createGameEntities(ECS &ecs);
void createMenuEntities(ECS &ecs);
void createMenuPlayerEntities(ECS &ecs);
void createConfigEntities(ECS &ecs);
void createConfigGeneralEntites(ECS &ecs);
void createConfigPlayer1Entites(ECS &ecs);
void createConfigPlayer2Entites(ECS &ecs);
void createMenuRoomEntities(ECS &ecs);
} // namespace rtype::client
