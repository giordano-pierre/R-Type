/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Text
*/

#include "components/Text.hpp"

namespace rtype::client {

Text::Text(const std::map<std::string, std::shared_ptr<std::string>> &str,
           const std::shared_ptr<sf::Font> &font, const TupleFloat &sizeInBox,
           const float &pos, int charSize, const sf::Color &color,
           const sf::Uint32 &style)
    : _sizeInBox(sizeInBox), _pos(pos), _color(color), _style(style),
      _charSize(charSize), _str(str) {
    _text.setFont(*font);
}

} // namespace rtype::client
