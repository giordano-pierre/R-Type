/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** clientTools
*/

#pragma once

#include "ECS/ECS.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace rtype::client {
struct TupleInt {
    int x;
    int y;
};

struct TupleUInt {
    unsigned int x;
    unsigned int y;
};

struct TupleFloat {
    float x;
    float y;
};

enum SceneType {
    MENU = 1,
    M_GENERAL,
    M_PLAYER, // à modifier
    M_ROOM,   // à faire
    M_IN_ROOM,
    MENUROOM,
    M_STAGE, // à faire
    M_PERSO, // à faire
    M_CONFIG,
    M_C_GENERAL,
    M_C_PLAYER1,
    M_C_PLAYER2,
    GAME,    // à améliorer
    G_PAUSE, // à faire
};

enum PowerupType {
    SHIELD,
    BONUSLIFE,
    TIMESTOP,
    ENNEMYDESTRUCTION,
};

enum UserInput {
    NOTHING = 0,
    ENTER,
    PAUSE,
    QUIT,
    RETURN,
    UP1P,
    UP1R,
    DOWN1P,
    DOWN1R,
    LEFT1P,
    LEFT1R,
    RIGHT1P,
    RIGHT1R,
    SHOOT1,
    SUPERSHOOT1,
    UP2P,
    UP2R,
    DOWN2P,
    DOWN2R,
    LEFT2P,
    LEFT2R,
    RIGHT2P,
    RIGHT2R,
    SHOOT2,
    SUPERSHOOT2,
};

float computeDist(TupleFloat a, TupleFloat b);
std::string convertInput(const sf::Keyboard::Key &key);
std::string getInput(std::map<UserInput, sf::Keyboard::Key> &input,
                     UserInput search);
void initGeneralInput(
    std::map<UserInput,
             std::pair<sf::Keyboard::Key, std::shared_ptr<std::string>>>
        &inputConfig);
void initPlay1Input(
    std::pair<std::map<UserInput, std::pair<sf::Keyboard::Key,
                                            std::shared_ptr<std::string>>>,
              std::map<UserInput, sf::Keyboard::Key>> &inputConfig);
void initPlay2Input(
    std::pair<std::map<UserInput, std::pair<sf::Keyboard::Key,
                                            std::shared_ptr<std::string>>>,
              std::map<UserInput, sf::Keyboard::Key>> &inputConfig);
void killMyEntity(ECS &ecs, Entity i);
} // namespace rtype::client
