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
        Window(TupleUInt = {1920, 1080});

        TupleUInt _size;
        std::map<UserInput, sf::Keyboard::Key> _inputConfig;
        TextureManager _myTextures;
        bool _displayHitboxs = false;
    };
}
std::ostream &operator<<(std::ostream &out, const Rtype::Client::Window &window);
