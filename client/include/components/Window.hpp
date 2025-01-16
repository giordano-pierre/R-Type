/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Window
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <ostream>

#include "TextureManager.hpp"
#include "clientTools.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

namespace rtype::client {
struct Window {
    Window(const std::string &, sf::Shader &shader, TupleUInt = {1920, 1080},
           TupleUInt = {1920, 1080});
    ~Window() = default;

    std::string _lang = "EN";
    TupleUInt _size;
    TupleUInt _serverSize;
    std::pair<std::map<UserInput, std::pair<sf::Keyboard::Key,
                                            std::shared_ptr<std::string>>>,
              std::map<UserInput, sf::Keyboard::Key>>
        _inputConfig;
    TextureManager _myTextures;
    std::shared_ptr<sf::Font> _font;
    bool _displayHitboxs = false;
    std::string _name1 = "player1";
    std::string _name2 = "player2";
    sf::RenderStates _renderState;
    bool _colorblind = false;
    bool _gameState = false;
    bool _master = false;
    std::string _idRoom;
};
} // namespace rtype::client

std::ostream &operator<<(std::ostream &out,
                         const rtype::client::Window &window);
