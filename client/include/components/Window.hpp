/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Window
*/

#pragma once

#include <map>
#include <ostream>
#include <SFML/Graphics.hpp>

#include "tools.hpp"
#include "TextureManager.hpp"

namespace Rtype::Client {
    struct Window {
        Window(const std::string &, TupleUInt = {1920, 1080}, TupleUInt = {1920, 1080});

        TupleUInt _size;
        TupleUInt _serverSize;
        std::map<UserInput, sf::Keyboard::Key> _inputConfig;
        TextureManager _myTextures;
        sf::Font _font;
        bool _displayHitboxs = false;
    };
}
std::ostream &operator<<(std::ostream &out, const Rtype::Client::Window &window);
