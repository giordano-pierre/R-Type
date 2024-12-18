/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Window
*/

#include "components/Window.hpp"

namespace Rtype::Client {

Window::Window(const std::string &fontPath, TupleUInt size,
               TupleUInt serverSize)
    : _size(size), _serverSize(serverSize) {
    initGeneralInput(_inputConfig.first);
    initPlay1Input(_inputConfig);
    initPlay2Input(_inputConfig);
    sf::Font tmp = sf::Font();
    tmp.loadFromFile(fontPath);
    _font = std::make_shared<sf::Font>(tmp);
}

} // namespace Rtype::Client

std::ostream &operator<<(std::ostream &out,
                         const Rtype::Client::Window &window) {
    out << "size: " << window._size.x << " " << window._size.y << std::endl;
    out << "serverSize: " << window._serverSize.x << " "
        << window._serverSize.y;
    return out;
}
