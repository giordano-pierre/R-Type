/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** PlayerInfo
*/

#pragma once

#include <string>

namespace rtype::client {

struct PlayerInfo {
    int _nbPlayer = 1;
    int _customPlayer = 1;
    std::string _name1 = "player1";
    std::string _color1 = "255.255.255";
    std::string _name2 = "player2";
    std::string _color2 = "255.255.255";
    std::string _spritePath1 = "assets/images/ship/red_ship.png";
    std::string _spritePath2 = "assets/images/ship/red_ship.png";
};

} // namespace rtype::client
