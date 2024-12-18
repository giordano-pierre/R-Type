/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Text
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

#include "tools.hpp"

namespace Rtype::Client {
struct Text {
    Text(const std::map<std::string, std::shared_ptr<std::string>> &, const std::shared_ptr<sf::Font> &,
         const TupleFloat &, const float &, int, const sf::Color &,
         const sf::Uint32 & = sf::Text::Style::Regular);
    ~Text() = default;

    std::map<std::string, std::shared_ptr<std::string>> _str;
    TupleFloat _sizeInBox;
    float _pos;
    sf::Color _color;
    sf::Uint32 _style;
    sf::Text _text;
    int _charSize;
    bool _needUpdate = true;
};
} // namespace Rtype::Client
