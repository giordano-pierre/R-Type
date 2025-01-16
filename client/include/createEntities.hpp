/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** createEntities
*/

#pragma once

#include "ECS/ECS.hpp"
#include "components/Window.hpp"

namespace rtype::client {

// Game
void createGameEntities(ECS &ecs, Window &myWindow);

// Menu Jeu
void createMenuEntities(ECS &ecs, Window &myWindow);
void createMenuGeneralEntities(ECS &ecs, Window &myWindow);
// void createMenuPlayerEntities(ECS &ecs, Window &myWindow);
void createMenuRoomEntities(ECS &ecs, Window &myWindow);

// Menu Config
void createConfigEntities(ECS &ecs, Window &myWindow);
void createConfigGeneralEntites(ECS &ecs, Window &myWindow);
void createConfigPlayer1Entites(ECS &ecs, Window &myWindow);
void createConfigPlayer2Entites(ECS &ecs, Window &myWindow);
} // namespace rtype::client
