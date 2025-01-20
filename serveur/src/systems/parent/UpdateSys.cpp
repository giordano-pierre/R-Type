/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** UpdateSys
*/

#include "systems/parent/UpdateSys.hpp"
#include <iostream>

namespace rtype::server {

void UpdateSys::operator()(ECS &ecs, const UpdateEvent &up_event,
                           SparseArray<Room> &rooms,
                           SparseArray<Child> &children) {
    for (size_t i = 0; i < rooms.size() && i < children.size(); ++i) {
        auto &ro = rooms[i];
        auto &child = children[i];

        if (ro && child && ro.value()._state == IN_GAME) {
            const auto &tags = child.value()._ecs_child.get_components<Tag>();
            const auto &players =
                child.value()._ecs_child.get_components<PlayerData>();
            const auto &positions =
                child.value()._ecs_child.get_components<Position>();
            const auto &velocities =
                child.value()._ecs_child.get_components<Velocity>();
            const auto &hitboxes =
                child.value()._ecs_child.get_components<HitBox>();
            const auto &healths =
                child.value()._ecs_child.get_components<Health>();
            const auto &scores =
                child.value()._ecs_child.get_components<Score>();

            ro.value()._lastUpdate = ((ro.value()._lastUpdate + 1) > 10)
                                         ? 1
                                         : (ro.value()._lastUpdate + 1);

            for (size_t j = 0; j < tags.size(); ++j) {
                nlohmann::json request;
                if (tags[j] && tags[j].value()._type != OTHER) {
                    request["id"] = tags[j].value()._id;
                    request["type"] = tags[j].value()._type;
                    request["lu"] = ro.value()._lastUpdate;
                    if (j < hitboxes.size() && hitboxes[j]) {
                        request["hit"] = {{"x", hitboxes[j].value().x},
                                          {"y", hitboxes[j].value().y}};
                    }
                    if (j < positions.size() && positions[j]) {
                        request["pos"] = {{"x", positions[j].value().x},
                                          {"y", positions[j].value().y}};
                    }
                    if (j < velocities.size() && velocities[j]) {
                        request["vel"] = {{"x", velocities[j].value().x},
                                          {"y", velocities[j].value().y}};
                    }
                    if (j < healths.size() && healths[j]) {
                        request["hp"] = healths[j].value()._health;
                    }
                    if (j < scores.size() && scores[j]) {
                        request["sc"] = scores[j].value()._score;
                    }
                    if (j < players.size() && players[j]) {
                        request["p_name"] = players[j].value()._name;
                        request["p_color"] = players[j].value()._color;
                    }
                    for (const auto &[uuid, _] : ro.value()._clients_uuid) {
                        ecs.post<RequestEvent>(
                            {SV_UPDATE_ENTITY, request, uuid});
                    }
                }
            }
        }
    }
}

} // namespace rtype::server
