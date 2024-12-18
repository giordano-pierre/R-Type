/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Selectable
*/

#include "components/Selectable.hpp"

namespace Rtype::Client {

Selectable::Selectable(std::shared_ptr<sf::Texture> texture,
                       std::function<void(ECS &, Entity)> sel,
                       std::function<void(ECS &, Entity)> desel)
    : _texture(texture), _sel(sel), _desel(desel) {
    auto tmp = _texture.get()->getSize();
    _size = {tmp.x, tmp.y};
    _sprite.setTexture(*_texture);
    _sprite.setOrigin(tmp.x / 2, tmp.y / 2);
}

} // namespace Rtype::Client
