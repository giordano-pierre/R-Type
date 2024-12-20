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
#include "tools.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

namespace rtype::client {
struct Window {
    Window(const std::string &, sf::Shader &shader, TupleUInt = {1920, 1080},
           TupleUInt = {1920, 1080});
    ~Window() = default;

    // Window(const Window& other) // Constructeur de copie
    //         : _lang(other._lang),
    //           _size(other._size),
    //           _serverSize(other._serverSize),
    //           _inputConfig(other._inputConfig),
    //           _myTextures(other._myTextures),
    //           _font(other._font),
    //           _displayHitboxs(other._displayHitboxs) {
    //         // Shader copy is not supported, reinitialize instead
    //     }

    //     Window& operator=(const Window& other) { // Opérateur d'assignation
    //         if (this != &other) {
    //             _lang = other._lang;
    //             _size = other._size;
    //             _serverSize = other._serverSize;
    //             _inputConfig = other._inputConfig;
    //             _myTextures = other._myTextures;
    //             _font = other._font;
    //             _displayHitboxs = other._displayHitboxs;
    //             // Shader copy is not supported, reinitialize instead
    //         }
    //         return *this;
    //     }

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
    sf::RenderStates _renderState; // ici shader
    bool _colorblind = false;
    bool _gameState = false;
};
} // namespace rtype::client
std::ostream &operator<<(std::ostream &out,
                         const rtype::client::Window &window);
