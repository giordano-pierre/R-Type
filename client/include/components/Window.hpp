/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Window
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <ostream>

#include "TextureManager.hpp"
#include "tools.hpp"

namespace Rtype::Client {
struct Window {
  Window(const std::string &, TupleUInt = {1920, 1080},
         TupleUInt = {1920, 1080});
  ~Window() = default;

    TupleUInt _size;
    TupleUInt _serverSize;
    std::pair<std::map<UserInput, sf::Keyboard::Key>,
              std::map<UserInput, sf::Keyboard::Key>>
        _inputConfig;
    TextureManager _myTextures;
    std::shared_ptr<sf::Font> _font;
    bool _displayHitboxs = false;
};
} // namespace Rtype::Client
std::ostream &operator<<(std::ostream &out,
                         const Rtype::Client::Window &window);
