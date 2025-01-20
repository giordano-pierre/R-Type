/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** SFMLObjects
*/

#pragma once

#include "TextureManager.hpp"

namespace rtype::client {

struct SFMLObjects {
    SFMLObjects(const std::string &fontPath, sf::Shader &shader);

    TextureManager _myTextures;
    std::shared_ptr<sf::Font> _font;
    sf::RenderStates _renderState;
};

} // namespace rtype::client
