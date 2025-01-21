/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** FireRateSys
*/

#include "systems/FireRateSys.hpp"

namespace rtype::client {

void FireRateSys::operator()(ECS &ecs, const TicEvent &e_tic,
                             SparseArray<Playable> &players) {
    for (size_t i = 0; i < players.size(); ++i) {
        auto &play = players[i];

        if (play && play.value()._newShot > 0) {
            play.value()._newShot -= 1;
        }
    }
}

} // namespace rtype::client
