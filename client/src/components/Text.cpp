/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Text
*/

#include "components/Text.hpp"

namespace Rtype::Client {

Text::Text(const std::string &str, const sf::Font &font,
           const TupleFloat &sizeInBox, const TupleFloat &posInBox,
           const sf::Color &color, const sf::Uint32 &style)
    : _sizeInBox(sizeInBox), _posInBox(posInBox), _color(color), _style(style)
{
    _text.setString(str);
    _text.setFont(font);
    auto tmp = _text.getLocalBounds();
    _text.setOrigin({tmp.left + tmp.width / 2, tmp.top + tmp.height / 2});
}

}
