/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PauseSys
*/

#include "systems/PauseSys.hpp"

namespace Rtype::Client {

void PauseSys::operator()(ECS &ecs, const InputEvent &e_input,
                          SparseArray<Drawable> &sprites)
{
    bool changeState = false;

    switch(e_input._event.type) {
        case sf::Event::KeyPressed:
            if (e_input._event.key.code == sf::Keyboard::P)
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

void PauseSys::operator()(ECS &ecs, const InputEvent &e_input,
                            SparseArray<Velocity> &velocities)
{
    bool changeState = false;

    switch(e_input._event.type) {
        case sf::Event::KeyPressed:
            if (e_input._event.key.code == sf::Keyboard::P)
                changeState = true;
                break;
        default:
            return;
    }

    for (size_t i = 0; i < velocities.size(); ++i) {
        auto &vel = velocities[i];

        if (vel && changeState)
            vel.value()._activated = !vel.value()._activated;
    }
}

}
