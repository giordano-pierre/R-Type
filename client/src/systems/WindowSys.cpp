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

void extractInput(ECS &ecs, sf::Event event, const std::map<UserInput, sf::Keyboard::Key> &inputConfig)
{
    bool isRegister = false;

    if (event.type != sf::Event::KeyPressed && event.type != sf::Event::KeyReleased) {
        ecs.post<InputEvent>({event, NOTHING});
        isRegister = true;
    } else {
        for (const auto [key, value] : inputConfig) {
            if (value == event.key.code) {
                ecs.post<InputEvent>({event, key});
                isRegister = true;
            }
        }
    }

    if (!isRegister)
        ecs.post<InputEvent>({event, NOTHING});
}

void WindowSys::operator()(ECS &ecs, const FrameEvent &,
                           const SparseArray<Window> &windows,
                           SparseArray<Position> &positions,
                           SparseArray<Hitbox> &hitboxs,
                           SparseArray<Drawable> &sprites)
{
    bool displayHitbox = (windows.size() > 0 && windows[0]) ? windows[0].value()._displayHitboxs : false;
    TupleUInt serverSize = (windows.size() > 0 && windows[0]) ? windows[0].value()._serverSize : TupleUInt{1920, 1080};
    auto inputConfig = (windows.size() > 0 && windows[0]) ? windows[0].value()._inputConfig : std::map<UserInput, sf::Keyboard::Key>();
    bool isResize = false;

    _window.clear();
    if (windows.size() > 0 && windows[0])
        resizeWindow(windows[0].value()._size, isResize);
    sf::Vector2u sizeWindow = _window.getSize();

    for (size_t i = 0; i < positions.size() && i < sprites.size() && i < hitboxs.size(); ++i) {
        auto &pos = positions[i];
        auto &sprite = sprites[i];
        auto &box = hitboxs[i];

        if (pos && sprite && box) {
            if (box.value()._needUpdate || isResize) {
                box.value()._server = {box.value()._coefSize.x * serverSize.x, box.value()._coefSize.y * serverSize.y};
                box.value()._client = {box.value()._coefSize.x * sizeWindow.x, box.value()._coefSize.y * sizeWindow.y};
                box.value()._needUpdate = false;
            }
            if (pos.value()._needUpdate || isResize) {
                pos.value()._client = {pos.value()._server.x * sizeWindow.x / serverSize.x, pos.value()._server.y * sizeWindow.y / serverSize.y};
                pos.value()._needUpdate = false;
            }
            sprite.value()._sprite.setPosition({pos.value()._client.x, pos.value()._client.y});
            sprite.value()._sprite.setTextureRect(sprite.value()._rectangle);
            sprite.value()._sprite.setScale({box.value()._client.x / sprite.value()._sizeFrame.x, box.value()._client.y / sprite.value()._sizeFrame.y});
            _window.draw(sprite.value()._sprite);

            if (box.value()._display && displayHitbox) {
                sf::RectangleShape borderRect(sf::Vector2f({box.value()._client.x, box.value()._client.y}));
                borderRect.setOrigin(box.value()._client.x / 2, box.value()._client.y / 2);
                borderRect.setFillColor(sf::Color::Transparent);
                borderRect.setOutlineColor(sf::Color::Red);
                borderRect.setOutlineThickness(2.0);
                borderRect.setPosition({pos.value()._client.x, pos.value()._client.y});
                _window.draw(borderRect);
            }
        }
    }
    _window.display();

    sf::Event event;

    while (_window.pollEvent(event)) {
        extractInput(ecs, event, inputConfig);
    }
}

}
