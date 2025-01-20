/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Room
*/

#pragma once

#include <memory>
#include <string>

namespace rtype::client {

struct Room {
    std::string _idRoom = "";
    bool _gameState = false;
    bool _master = false;
    std::shared_ptr<std::string> _name = std::make_shared<std::string>("test");
    std::string _levelFile = "";
    int _diff = 3;
    int _nbPlayer = 0;
};

} // namespace rtype::client
