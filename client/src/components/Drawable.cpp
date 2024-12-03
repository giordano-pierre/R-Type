/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Drawable
*/

#include "components/Drawable.hpp"

namespace Rtype::Client{

Drawable::Drawable(std::shared_ptr<sf::Texture> texture, TupleInt sizeTexture, TupleInt sizeFrame, int nbFrame, float percSize)
    : _texture(texture), _sizeTexture(sizeTexture), _sizeFrame(sizeFrame), _nbFrame(nbFrame), _currentFrame(0), _percSize(percSize)
{
    _rectangle = sf::IntRect(0, 0, _sizeFrame.x, _sizeFrame.y);
    _sprite = sf::Sprite(*_texture);
    _sprite.setTextureRect(_rectangle);
    _sprite.setOrigin({_sizeFrame.x / float(2.0), _sizeFrame.y / float(2.0)});
}

}
