/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Text
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

#include "tools.hpp"

namespace Rtype::Client {
    struct Text {
        Text(const std::string &, const std::shared_ptr<sf::Font> &,
             const TupleFloat &, const float &, int,
             const sf::Color &, const sf::Uint32 & = sf::Text::Style::Regular);

        TupleFloat _sizeInBox;
        float _pos;
        sf::Color _color;
        sf::Uint32 _style;
        sf::Text _text;
        int _charSize;
        bool _needUpdate = true;
    };
}
