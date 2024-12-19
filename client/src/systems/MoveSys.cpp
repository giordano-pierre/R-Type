/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MoveSys
*/

#include "systems/MoveSys.hpp"

namespace rtype::client {

void MoveSys::operator()(ECS &ecs, const InputEvent &e_input,
                         const SparseArray<Playable> &players,
                         SparseArray<Velocity> &velocities) {
    TupleInt newValue = {-1, -1};

    switch (e_input._myEvent) {
    case LEFT1P:
        newValue.x = -8;
        break;
    case LEFT1R:
        newValue.x = 0;
        break;
    case RIGHT1P:
        newValue.x = 8;
        break;
    case RIGHT1R:
        newValue.x = 0;
        break;
    case UP1P:
        newValue.y = -8;
        break;
    case UP1R:
        newValue.y = 0;
        break;
    case DOWN1P:
        newValue.y = 8;
        break;
    case DOWN1R:
        newValue.y = 0;
        break;
    default:
        break;
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
                         const SparseArray<Velocity> &velocities) {
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

} // namespace rtype::client
