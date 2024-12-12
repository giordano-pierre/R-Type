/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Text
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "tools.hpp"

namespace Rtype::Client {
struct Text {
  Text(const std::string &, const sf::Font &, const TupleFloat &,
       const TupleFloat &, const sf::Color &,
       const sf::Uint32 & = sf::Text::Style::Regular);

  TupleFloat _sizeInBox;
  TupleFloat _posInBox;
  sf::Color _color;
  sf::Uint32 _style;
  sf::Text _text;
  bool _needUpdate = true;
};
} // namespace Rtype::Client
