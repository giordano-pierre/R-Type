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

void extractInput(ECS &ecs, sf::Event event,
                  const std::pair<std::map<UserInput, sf::Keyboard::Key>,
                        std::map<UserInput, sf::Keyboard::Key>> &inputConfig)
{
    bool isRegister = false;

    if (event.type == sf::Event::KeyPressed) {
        for (const auto [key, value] : inputConfig.first) {
            if (value == event.key.code) {
                ecs.post<InputEvent>({event, key});
                isRegister = true;
            }
        }
    }
    if (event.type == sf::Event::KeyReleased) {
        for (const auto [key, value] : inputConfig.second) {
            if (value == event.key.code) {
                ecs.post<InputEvent>({event, key});
                isRegister = true;
            }
        }
    }
    if (!isRegister)
        ecs.post<InputEvent>({event, NOTHING});
}

void WindowSys::updateInfo(SparseArray<Position> &positions,
                           SparseArray<Hitbox> &hitboxs,
                           bool isResize, sf::Vector2u sizeClient, TupleUInt serverSize)
{
    for (size_t i = 0; i < positions.size() && i < hitboxs.size(); ++i) {
        auto &pos = positions[i];
        auto &box = hitboxs[i];

        if (box && (box.value()._needUpdate || isResize)) {
            box.value()._server = {box.value()._coefSize.x * serverSize.x, box.value()._coefSize.y * serverSize.y};
            box.value()._client = {box.value()._coefSize.x * sizeClient.x, box.value()._coefSize.y * sizeClient.y};
            box.value()._needUpdate = false;
        }
        if (pos && (pos.value()._needUpdate || isResize)) {
            pos.value()._client = {pos.value()._server.x * sizeClient.x / serverSize.x, pos.value()._server.y * sizeClient.y / serverSize.y};
            pos.value()._needUpdate = false;
        }
    }
}

void WindowSys::drawSprite(SparseArray<Position> &positions,
                           SparseArray<Hitbox> &hitboxs,
                           SparseArray<Drawable> &sprites)
{
    for (size_t i = 0; i < positions.size() && i < hitboxs.size() && i < sprites.size(); ++i) {
        auto &pos = positions[i];
        auto &box = hitboxs[i];
        auto &sprite = sprites[i];

        if (pos && box && sprite) {
            sprite.value()._sprite.setPosition({pos.value()._client.x, pos.value()._client.y});
            sprite.value()._sprite.setTextureRect(sprite.value()._rectangle);
            sprite.value()._sprite.setScale({box.value()._client.x / sprite.value()._sizeFrame.x, box.value()._client.y / sprite.value()._sizeFrame.y});
            _window.draw(sprite.value()._sprite);
        }
    }
}

void WindowSys::drawText(SparseArray<Position> &positions,
                           SparseArray<Hitbox> &hitboxs,
                           SparseArray<Text> &texts, bool isResize)
{
    for (size_t i = 0; i < positions.size() && i < hitboxs.size() && i < texts.size(); ++i) {
        auto &pos = positions[i];
        auto &box = hitboxs[i];
        auto &tex = texts[i];

        if (pos && box && tex) {
            if (tex.value()._needUpdate) {
                tex.value()._text.setFillColor(tex.value()._color);
                tex.value()._text.setStyle(tex.value()._style);
            }
            TupleFloat sizeGoal = {tex.value()._sizeInBox.x * box.value()._client.x, tex.value()._sizeInBox.y * box.value()._client.y};
            TupleFloat boxOrigine = {pos.value()._client.x - (box.value()._client.x / 2), pos.value()._client.y - (box.value()._client.y / 2)};
            TupleFloat posInBox = {(box.value()._client.x - sizeGoal.x) * tex.value()._posInBox.x, (box.value()._client.y - sizeGoal.y) * tex.value()._posInBox.y};
            auto currentSize = tex.value()._text.getLocalBounds();
            auto coef = std::min(sizeGoal.x / currentSize.width, sizeGoal.y / currentSize.height);
            tex.value()._text.setScale({coef, coef});
            tex.value()._text.setPosition({boxOrigine.x + posInBox.x + (sizeGoal.x / 2), boxOrigine.y + posInBox.y + (sizeGoal.y / 2)});
            _window.draw(tex.value()._text);
        }
    }
}

void WindowSys::drawHitboxes(SparseArray<Position> &positions,
                             SparseArray<Hitbox> &hitboxs, bool draw)
{
    for (size_t i = 0; i < positions.size() && i < hitboxs.size(); ++i) {
        auto &pos = positions[i];
        auto &box = hitboxs[i];

        if (pos && box && box.value()._display && draw) {
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

void WindowSys::operator()(ECS &ecs, const FrameEvent &,
                           const SparseArray<Window> &windows,
                           SparseArray<Position> &positions,
                           SparseArray<Hitbox> &hitboxs,
                           SparseArray<Drawable> &sprites,
                           SparseArray<Text> &texts)
{
    bool displayHitbox = (windows.size() > 0 && windows[0]) ? windows[0].value()._displayHitboxs : false;
    TupleUInt serverSize = (windows.size() > 0 && windows[0]) ? windows[0].value()._serverSize : TupleUInt{1920, 1080};
    auto inputConfig = (windows.size() > 0 && windows[0]) ? windows[0].value()._inputConfig
                        : std::pair<std::map<UserInput, sf::Keyboard::Key>, std::map<UserInput, sf::Keyboard::Key>>();
    bool isResize = false;

    _window.clear();
    if (windows.size() > 0 && windows[0])
        resizeWindow(windows[0].value()._size, isResize);
    sf::Vector2u sizeWindow = _window.getSize();

    updateInfo(positions, hitboxs, isResize, sizeWindow, serverSize);
    drawSprite(positions, hitboxs, sprites);
    drawText(positions, hitboxs, texts, isResize);
    drawHitboxes(positions, hitboxs, displayHitbox);
    _window.display();

    sf::Event event;

    while (_window.pollEvent(event))
        extractInput(ecs, event, inputConfig);
}

}
