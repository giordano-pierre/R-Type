/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MoveSys
*/

#include "systems/MoveSys.hpp"
#include "events/RequestEvent.hpp"

namespace rtype::client {

void MoveSys::operator()(ECS &ecs, const InputEvent &e_input,
                         const SparseArray<Playable> &players,
                         SparseArray<Velocity> &velocities,
                         const SparseArray<Tag> &tags) {
    TupleInt newValue = {-1, -1};
    std::string uuid1 = "";
    for (size_t i = 0; i < tags.size() && i < players.size(); ++i) {
        const auto &play = players[i];
        const auto &tag = tags[i];

        if (play && tag && play.value()._id == 1)
            uuid1 = tag.value()._id;
    }

    if (uuid1.empty())
        return;

    switch (e_input._myEvent) {
    case LEFT1P:
        newValue.x = -8;
        ecs.post<RequestEvent>({CL_MOVE, {{"idp", uuid1}, {"e_type", "left"}}});
        break;
    case LEFT1R:
        newValue.x = 0;
        ecs.post<RequestEvent>(
            {CL_MOVE, {{"idp", uuid1}, {"e_type", "releasedX"}}});
        break;
    case RIGHT1P:
        newValue.x = 8;
        ecs.post<RequestEvent>(
            {CL_MOVE, {{"idp", uuid1}, {"e_type", "right"}}});
        break;
    case RIGHT1R:
        newValue.x = 0;
        ecs.post<RequestEvent>(
            {CL_MOVE, {{"idp", uuid1}, {"e_type", "releasedX"}}});
        break;
    case UP1P:
        newValue.y = -8;
        ecs.post<RequestEvent>({CL_MOVE, {{"idp", uuid1}, {"e_type", "up"}}});
        break;
    case UP1R:
        newValue.y = 0;
        ecs.post<RequestEvent>(
            {CL_MOVE, {{"idp", uuid1}, {"e_type", "releasedY"}}});
        break;
    case DOWN1P:
        newValue.y = 8;
        ecs.post<RequestEvent>({CL_MOVE, {{"idp", uuid1}, {"e_type", "down"}}});
        break;
    case DOWN1R:
        newValue.y = 0;
        ecs.post<RequestEvent>(
            {CL_MOVE, {{"idp", uuid1}, {"e_type", "releasedY"}}});
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
