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
    : _window(mode, title, style, settings), _title(title)
{
}

void WindowSys::resizeWindow(TupleUInt newSize, bool &isResize)
{
    sf::Vector2u sizeWindow = _window.getSize();

    if (sizeWindow.x == newSize.x && sizeWindow.y == newSize.y)
        return;
    _window.close();
    _window.create({newSize.x, newSize.y, 32}, _title, sf::Style::Titlebar | sf::Style::Close);
    isResize = true;
}

void WindowSys::operator()(ECS &ecs, const FrameEvent &,
                           const SparseArray<Window> &windows,
                           const SparseArray<Position> &positions,
                           SparseArray<Hitbox> &hitboxs,
                           SparseArray<Drawable> &sprites)
{
    bool displayHitbox = (windows.size() > 0 && windows[0]) ? windows[0].value()._displayHitboxs : false;
    bool isResize = false;

    _window.clear();
    if (windows.size() > 0 && windows[0])
        resizeWindow(windows[0].value()._size, isResize);
    sf::Vector2u sizeWindow = _window.getSize();

    for (size_t i = 0; i < positions.size() && i < sprites.size() && i < hitboxs.size(); ++i) {
        auto const &pos = positions[i];
        auto &sprite = sprites[i];
        auto &box = hitboxs[i];

        if (pos && sprite && box) {
            if (box.value()._needUpdate || isResize) {
                box.value()._size = {box.value()._coefSize.x * sizeWindow.x, box.value()._coefSize.y * sizeWindow.y};
                box.value()._needUpdate = false;
            }
            sprite.value()._sprite.setPosition({pos.value()._current.x, pos.value()._current.y});
            sprite.value()._sprite.setTextureRect(sprite.value()._rectangle);
            sprite.value()._sprite.setScale({box.value()._size.x / sprite.value()._sizeFrame.x, box.value()._size.y / sprite.value()._sizeFrame.y});
            _window.draw(sprite.value()._sprite);

            if (box.value()._display && displayHitbox) {
                sf::RectangleShape borderRect(sf::Vector2f({box.value()._size.x, box.value()._size.y}));
                borderRect.setOrigin(box.value()._size.x / 2, box.value()._size.y / 2);
                borderRect.setFillColor(sf::Color::Transparent);
                borderRect.setOutlineColor(sf::Color::Red);
                borderRect.setOutlineThickness(2.0);
                borderRect.setPosition({pos.value()._current.x, pos.value()._current.y});
                _window.draw(borderRect);
            }
        }
    }
    _window.display();

    sf::Event event;

    while (_window.pollEvent(event)) {
        ecs.post<InputEvent>({event});
    }
}

}
