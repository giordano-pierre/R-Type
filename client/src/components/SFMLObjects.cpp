/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** SFMLObjects
*/

#include "components/SFMLObjects.hpp"

namespace rtype::client {

SFMLObjects::SFMLObjects(const std::string &fontPath, sf::Shader &shader)
{
    sf::Font tmp = sf::Font();
    tmp.loadFromFile(fontPath);
    _font = std::make_shared<sf::Font>(tmp);
    _renderState.shader = &shader;
}


}