/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** DrawableSys
*/

#include "systems/DrawableSys.hpp"
#include <iostream>

namespace Rtype::Client {

void DrawableSys::operator()(ECS &ecs, const FrameEvent &,
                SparseArray<Drawable> &sprites)
{
    for (size_t i = 0; i < sprites.size(); ++i) {
        auto &sprite = sprites[i];
        if (!sprite || !sprite.value()._activated)
            continue;
        if (sprite.value()._currentFrame == 0 || sprite.value()._nbFrame == 1) {
            sprite.value()._currentFrame = 1;
            continue;
        }
        sprite.value()._currentFrame += 1;
        if (sprite.value()._currentFrame > sprite.value()._nbFrame) {
            sprite.value()._currentFrame = 1;
            sprite.value()._rectangle.left = 0;
            sprite.value()._rectangle.top = 0;
        }
        sprite.value()._rectangle.left += sprite.value()._sizeFrame.x;
        if (sprite.value()._rectangle.left > (sprite.value()._sizeTexture.x - sprite.value()._sizeFrame.x)) {
            sprite.value()._rectangle.left = 0;
            sprite.value()._rectangle.top += sprite.value()._sizeFrame.y;
        }
        if (sprite.value()._rectangle.top > sprite.value()._sizeTexture.y) {
            sprite.value()._rectangle.left = 0;
            sprite.value()._rectangle.top = 0;
            sprite.value()._currentFrame = 1;
        }
    }
}

void DrawableSys::operator()(ECS &ecs, const InputEvent &e_input,
                SparseArray<Drawable> &sprites)
{
    bool changeState = false;

    switch(e_input.event.type) {
        case sf::Event::KeyPressed:
            if (e_input.event.key.code == sf::Keyboard::Space)
                changeState = true;
                break;
        default:
            return;
    }

    for (size_t i = 0; i < sprites.size(); ++i) {
        auto &sprite = sprites[i];

        if (sprite && changeState)
            sprite.value()._activated = !sprite.value()._activated;
    }
}

}
