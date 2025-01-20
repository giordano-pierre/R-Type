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
    std::string _name1 = "player1";
    std::string _color1 = "red";
    std::string _name2 = "player2";
    std::string _color2 = "red";
};

} // namespace rtype::client
