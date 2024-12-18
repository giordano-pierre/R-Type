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

namespace Rtype::Client {

void ShootSys::operator()(ECS &ecs, const InputEvent &e_input,
                          SparseArray<Window> &windows,
                          const SparseArray<Playable> &players,
                          const SparseArray<Position> &positions,
                          const SparseArray<Hitbox> &hitboxs) {
    bool player1Shoot = false;

    switch (e_input._myEvent) {
    case SHOOT1:
        player1Shoot = true;
        break;
    default:
        return;
    }

    for (size_t i = 0;
         i < players.size() && i < positions.size() && i < hitboxs.size();
         ++i) {
        const auto &play = players[i];
        const auto &pos = positions[i];
        const auto &box = hitboxs[i];

        if (play && pos && box && player1Shoot) {
            Entity shot = ecs.spawn_entity();
            ecs.add_component<Position>(
                shot, {pos.value()._server.x + (box.value()._server.x / 2),
                       pos.value()._server.y});
            ecs.add_component<Velocity>(shot, {15, 0});
            ecs.add_component<Tag>(shot, {SHOT});
            ecs.add_component<Hitbox>(shot, {{0.07, 0.05}});
            ecs.add_component<Drawable>(
                shot, {windows[0].value()._myTextures.getTexture(
                           "assets/images/shot/purple_shot.png"),
                       {251, 144},
                       {251, 144},
                       1,
                       2});
        }
    }
}
} // namespace Rtype::Client
