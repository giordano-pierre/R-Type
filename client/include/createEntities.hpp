/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** createEntities
*/

#pragma once

#include "ECS/ECS.hpp"
#include "components/Configs.hpp"
#include "components/PlayerInfo.hpp"
#include "components/Room.hpp"
#include "components/SFMLObjects.hpp"
#include "events/ReceiveEvent.hpp"

namespace rtype::client {

// Game
void createGameEntities(ECS &ecs, const Configs &myConfig,
                        SFMLObjects &SFMLObj);

// Menu Jeu
void createMenuEntities(ECS &ecs, const Configs &myConfig,
                        SFMLObjects &SFMLObj);
void createMenuGeneralEntities(ECS &ecs, const Configs &myConfig,
                               SFMLObjects &SFMLObj);
void createMenuPlayerEntities(ECS &ecs, const Configs &myConfig,
                              SFMLObjects &SFMLObj);
void createMenuRoomEntities(ECS &ecs, const ReceiveEvent &rec_event,
                            const Configs &myConfig, SFMLObjects &SFMLObj,
                            PlayerInfo &playerInfo, Room &myRoom);
void createMenuInRoomEntities(ECS &ecs, const Configs &myConfig,
                              SFMLObjects &SFMLObj, Room &myRoom);
void createCustomEntities(ECS &ecs, const Configs &myConfig,
                        SFMLObjects &SFMLObj);

// Menu Config
void createConfigEntities(ECS &ecs, const Configs &myConfig,
                          SFMLObjects &SFMLObj);
void createConfigGeneralEntites(ECS &ecs, const Configs &myConfig,
                                SFMLObjects &SFMLObj);
void createConfigPlayer1Entites(ECS &ecs, const Configs &myConfig,
                                SFMLObjects &SFMLObj);
void createConfigPlayer2Entites(ECS &ecs, const Configs &myConfig,
                                SFMLObjects &SFMLObj);
void createMenuRoomEntities(ECS &ecs, Configs &config, SFMLObjects &SFMLObj);
} // namespace rtype::client
