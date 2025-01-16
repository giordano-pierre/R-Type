/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** PlayerData
*/

#pragma once

#include <ostream>

namespace rtype::client {

struct PlayerData {
    PlayerData(const std::string &name, const std::string &color)
        : _name(name), _color(color){};

    std::string _name;
    std::string _color;
};

} // namespace rtype::client
