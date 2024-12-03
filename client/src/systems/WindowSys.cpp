/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** WindowSys
*/

#include "systems/WindowSys.hpp"
#include "events/InputEvent.hpp"

#include <iostream>

namespace Rtype::Client {

WindowSys::WindowSys(sf::VideoMode mode, const sf::String &title,
                     sf::Uint32 style, const sf::ContextSettings &settings)
    : _window(mode, title, style, settings)
{
}

void WindowSys::operator()(ECS &ecs, const FrameEvent &,
                           const SparseArray<Position> &positions,
                           SparseArray<Drawable> &sprites)
{
    _window.clear();
    for (size_t i = 0; i < positions.size() && i < sprites.size(); ++i) {
        auto const &pos = positions[i];
        auto &sprite = sprites[i];

        if (pos && sprite) {
            sprite.value()._sprite.setPosition({pos.value()._current.x, pos.value()._current.y});
            sprite.value()._sprite.setTextureRect(sprite.value()._rectangle);
            float size = sprite.value()._percSize * _window.getSize().y;
            sprite.value()._sprite.setScale({size / sprite.value()._sizeFrame.y, size / sprite.value()._sizeFrame.y});
            _window.draw(sprite.value()._sprite);
        }
    }
    _window.display();

    sf::Event event;

    while (_window.pollEvent(event)) {
        ecs.post<InputEvent>({event});
    }
}

}
