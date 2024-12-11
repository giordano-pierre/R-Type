/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Window
*/

#include "components/Window.hpp"

namespace Rtype::Client {

Window::Window(const std::string &fontPath, TupleUInt size, TupleUInt serverSize)
    : _size(size), _serverSize(serverSize)
{
    this->_inputConfig.insert({UP, sf::Keyboard::Up});
    this->_inputConfig.insert({DOWN, sf::Keyboard::Down});
    this->_inputConfig.insert({LEFT, sf::Keyboard::Left});
    this->_inputConfig.insert({RIGHT, sf::Keyboard::Right});
    this->_inputConfig.insert({ENTER, sf::Keyboard::Space});
    this->_inputConfig.insert({PAUSE, sf::Keyboard::P});
    this->_inputConfig.insert({SHOOT, sf::Keyboard::Space});
    this->_inputConfig.insert({SUPERSHOOT, sf::Keyboard::Enter});
    this->_inputConfig.insert({RETURN, sf::Keyboard::Q});
    this->_inputConfig.insert({QUIT, sf::Keyboard::Escape});
    _font.loadFromFile(fontPath);
}

}

std::ostream &operator<<(std::ostream &out, const Rtype::Client::Window &window)
{
    out << "size: " << window._size.x << " " << window._size.y << std::endl;
    out << "serverSize: " << window._serverSize.x << " " << window._serverSize.y;
    return out;
}
