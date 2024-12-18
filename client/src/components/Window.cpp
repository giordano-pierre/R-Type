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
    std::map<UserInput, sf::Keyboard::Key> pressed;
    std::map<UserInput, sf::Keyboard::Key> released;
    pressed.insert({ENTER, sf::Keyboard::Space});
    pressed.insert({PAUSE, sf::Keyboard::P});
    pressed.insert({RETURN, sf::Keyboard::Q});
    pressed.insert({QUIT, sf::Keyboard::Escape});
    pressed.insert({UP1P, sf::Keyboard::Up});
    pressed.insert({DOWN1P, sf::Keyboard::Down});
    pressed.insert({LEFT1P, sf::Keyboard::Left});
    pressed.insert({RIGHT1P, sf::Keyboard::Right});
    released.insert({UP1R, sf::Keyboard::Up});
    released.insert({DOWN1R, sf::Keyboard::Down});
    released.insert({LEFT1R, sf::Keyboard::Left});
    released.insert({RIGHT1R, sf::Keyboard::Right});
    pressed.insert({SHOOT1, sf::Keyboard::Space});
    pressed.insert({SUPERSHOOT1, sf::Keyboard::Enter});
    _inputConfig = {pressed, released};
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
