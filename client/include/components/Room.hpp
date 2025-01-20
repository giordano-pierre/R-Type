/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Room
*/

#pragma once

#include <string>

namespace rtype::client {

struct Room {
    std::string _idRoom = "";
    bool _gameState = false;
    bool _master = false;
    std::string _level = "";
};

} // namespace rtype::client
