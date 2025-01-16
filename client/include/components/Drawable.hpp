/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Drawable
*/
#include <SFML/Graphics.hpp>
#include <memory>

#include "clientTools.hpp"

#pragma once
namespace rtype::client {
struct Drawable {
    Drawable(const std::shared_ptr<sf::Texture> texture,
             const TupleInt sizeTexture, const TupleInt sizeFrame, int nbFrame,
             int order = 0);
    ~Drawable() = default;

    int _nbFrame;
    int _currentFrame;
    TupleInt _sizeTexture;
    TupleInt _sizeFrame;
    bool _activated = true;
    int _order;

    std::shared_ptr<sf::Texture> _texture;
    sf::IntRect _rectangle;
    sf::Sprite _sprite;
};
} // namespace rtype::client
