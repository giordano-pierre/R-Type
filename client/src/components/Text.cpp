/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Text
*/

#include "components/Text.hpp"

namespace Rtype::Client {

Text::Text(const std::string &str, const sf::Font &font,
           const TupleFloat &sizeInBox, const float &pos, int charSize,
           const sf::Color &color, const sf::Uint32 &style)
    : _sizeInBox(sizeInBox), _pos(pos), _color(color), _style(style), _charSize(charSize)
{
    _text.setString(str);
    _text.setFont(font);
}

}
