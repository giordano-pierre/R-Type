/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Drawable
*/
#include <SFML/Graphics.hpp>
#include <memory>

#include "tools.hpp"

#pragma once
namespace Rtype::Client {
    struct Drawable {
        Drawable(const std::shared_ptr<sf::Texture> texture, const TupleInt sizeTexture, const TupleInt sizeFrame, int nbFrame);
        ~Drawable() = default;

        int _nbFrame;
        int _currentFrame;
        TupleInt _sizeTexture;
        TupleInt _sizeFrame;
        bool _activated = true;

        std::shared_ptr<sf::Texture> _texture;
        sf::IntRect _rectangle;
        sf::Sprite _sprite;
    };
}
