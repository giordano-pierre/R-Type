/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Configs
*/

#pragma once

#include "clientTools.hpp"

namespace rtype::client {

struct Configs {
    Configs(TupleUInt size, TupleUInt serverSize);

    TupleUInt _size;
    TupleUInt _serverSize;
    std::pair<std::map<UserInput, std::pair<sf::Keyboard::Key,
                                            std::shared_ptr<std::string>>>,
              std::map<UserInput, sf::Keyboard::Key>>
        _inputConfig;
    std::string _lang = "EN";
    bool _colorblind = false;
    bool _displayHitboxs = false;
};

} // namespace rtype::client
