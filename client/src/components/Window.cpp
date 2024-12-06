/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Window
*/

#include "components/Window.hpp"

namespace Rtype::Client {

Window::Window(TupleUInt size) : _size(size)
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
}

}

std::ostream &operator<<(std::ostream &out, const Rtype::Client::Window &window)
{
    out << "size: " << window._size.x << " " << window._size.y << std::endl;
    return out;
}
