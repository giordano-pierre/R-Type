/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ShootSys
*/

#include "systems/ShootSys.hpp"
#include "components/Drawable.hpp"
#include "components/Tag.hpp"
#include "components/Velocity.hpp"
#include "events/RequestEvent.hpp"

namespace rtype::client {

void ShootSys::operator()(ECS &ecs, const InputEvent &e_input,
                          SparseArray<Window> &windows,
                          const SparseArray<Playable> &players,
                          const SparseArray<Position> &positions,
                          const SparseArray<Hitbox> &hitboxs,
                          const SparseArray<Tag> &tags) {
    bool player1Shoot = false;

    switch (e_input._myEvent) {
    case SHOOT1:
        player1Shoot = true;
        break;
    default:
        return;
    }

    for (size_t i = 0; i < players.size() && i < positions.size() &&
                       i < hitboxs.size() && i < tags.size();
         ++i) {
        const auto &play = players[i];
        const auto &pos = positions[i];
        const auto &box = hitboxs[i];
        const auto &tag = tags[i];

        if (play && pos && box && tag && player1Shoot &&
            play.value()._id == 1) {
            ecs.post<RequestEvent>({CL_SHOOT, {{"idp", tag.value()._id}}});
        }
    }
}
} // namespace rtype::client
