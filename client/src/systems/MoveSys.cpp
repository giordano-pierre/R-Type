/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MoveSys
*/

#include "systems/MoveSys.hpp"
#include <iostream>

namespace Rtype::Client {

void MoveSys::operator()(ECS &ecs, const InputEvent &e_input,
                             const SparseArray<Playable> &players,
                             SparseArray<Velocity> &velocities)
{
    TupleInt newValue = {-1, -1};

    switch(e_input._event.type) {
        case sf::Event::KeyPressed:
            if (e_input._event.key.code == sf::Keyboard::Left)
                newValue.x = -5;
            if (e_input._event.key.code == sf::Keyboard::Right)
                newValue.x = 5;
            if (e_input._event.key.code == sf::Keyboard::Up)
                    newValue.y = -5;
            if (e_input._event.key.code == sf::Keyboard::Down)
                    newValue.y = 5;
            break;
        case sf::Event::KeyReleased:
            if (e_input._event.key.code == sf::Keyboard::Left ||
                e_input._event.key.code == sf::Keyboard::Right)
                newValue.x = 0;
            if (e_input._event.key.code == sf::Keyboard::Up ||
                e_input._event.key.code == sf::Keyboard::Down)
                newValue.y = 0;
            break;
        default:
            return;
    }

    for (size_t i = 0; i < velocities.size() && i < players.size(); ++i) {
        auto &vel = velocities[i];
        auto &play = players[i];

        if (vel && play && newValue.x != -1)
            vel.value()._current.x = newValue.x;
        if (vel && play && newValue.y != -1)
            vel.value()._current.y = newValue.y;
    }
}

void MoveSys::operator()(ECS &ecs, const TicEvent &e_tic,
                        SparseArray<Position> &positions,
                        const SparseArray<Velocity> &velocities)
{
    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
        auto &pos = positions[i];
        const auto &vel = velocities[i];

        if (pos && vel && vel.value()._activated) {
            pos.value()._server.x += vel.value()._current.x;
            pos.value()._server.y += vel.value()._current.y;
            pos.value()._needUpdate = true;
        }
    }
}

}
