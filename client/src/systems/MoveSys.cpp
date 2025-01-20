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
    TupleInt newValue1 = {-1, -1};
    TupleInt newValue2 = {-1, -1};
    std::string uuid1 = "";
    std::string uuid2 = "";
    for (size_t i = 0; i < tags.size() && i < players.size(); ++i) {
        const auto &play = players[i];
        const auto &tag = tags[i];

        if (play && tag && play.value()._id == 1)
            uuid1 = tag.value()._id;
        if (play && tag && play.value()._id == 2)
            uuid2 = tag.value()._id;
    }

    if (!uuid1.empty()) {
        switch (e_input._myEvent) {
        case LEFT1P:
            newValue1.x = -8;
            ecs.post<RequestEvent>(
                {CL_MOVE, {{"idp", uuid1}, {"e_type", "left"}}});
            break;
        case LEFT1R:
            newValue1.x = 0;
            ecs.post<RequestEvent>(
                {CL_MOVE, {{"idp", uuid1}, {"e_type", "releasedX"}}});
            break;
        case RIGHT1P:
            newValue1.x = 8;
            ecs.post<RequestEvent>(
                {CL_MOVE, {{"idp", uuid1}, {"e_type", "right"}}});
            break;
        case RIGHT1R:
            newValue1.x = 0;
            ecs.post<RequestEvent>(
                {CL_MOVE, {{"idp", uuid1}, {"e_type", "releasedX"}}});
            break;
        case UP1P:
            newValue1.y = -8;
            ecs.post<RequestEvent>(
                {CL_MOVE, {{"idp", uuid1}, {"e_type", "up"}}});
            break;
        case UP1R:
            newValue1.y = 0;
            ecs.post<RequestEvent>(
                {CL_MOVE, {{"idp", uuid1}, {"e_type", "releasedY"}}});
            break;
        case DOWN1P:
            newValue1.y = 8;
            ecs.post<RequestEvent>(
                {CL_MOVE, {{"idp", uuid1}, {"e_type", "down"}}});
            break;
        case DOWN1R:
            newValue1.y = 0;
            ecs.post<RequestEvent>(
                {CL_MOVE, {{"idp", uuid1}, {"e_type", "releasedY"}}});
            break;
        default:
            break;
        }
    }
    if (!uuid2.empty()) {
        switch (e_input._myEvent) {
        case LEFT2P:
            newValue2.x = -8;
            ecs.post<RequestEvent>(
                {CL_MOVE, {{"idp", uuid2}, {"e_type", "left"}}});
            break;
        case LEFT2R:
            newValue2.x = 0;
            ecs.post<RequestEvent>(
                {CL_MOVE, {{"idp", uuid2}, {"e_type", "releasedX"}}});
            break;
        case RIGHT2P:
            newValue2.x = 8;
            ecs.post<RequestEvent>(
                {CL_MOVE, {{"idp", uuid2}, {"e_type", "right"}}});
            break;
        case RIGHT2R:
            newValue2.x = 0;
            ecs.post<RequestEvent>(
                {CL_MOVE, {{"idp", uuid2}, {"e_type", "releasedX"}}});
            break;
        case UP2P:
            newValue2.y = -8;
            ecs.post<RequestEvent>(
                {CL_MOVE, {{"idp", uuid2}, {"e_type", "up"}}});
            break;
        case UP2R:
            newValue2.y = 0;
            ecs.post<RequestEvent>(
                {CL_MOVE, {{"idp", uuid2}, {"e_type", "releasedY"}}});
            break;
        case DOWN2P:
            newValue2.y = 8;
            ecs.post<RequestEvent>(
                {CL_MOVE, {{"idp", uuid2}, {"e_type", "down"}}});
            break;
        case DOWN2R:
            newValue2.y = 0;
            ecs.post<RequestEvent>(
                {CL_MOVE, {{"idp", uuid2}, {"e_type", "releasedY"}}});
            break;
        default:
            break;
        }
    }

    for (size_t i = 0; i < velocities.size() && i < players.size(); ++i) {
        auto &vel = velocities[i];
        auto &play = players[i];

        if (vel && play && play.value()._id == 1 && newValue1.x != -1)
            vel.value()._current.x = newValue1.x;
        if (vel && play && play.value()._id == 1 && newValue1.y != -1)
            vel.value()._current.y = newValue1.y;
        if (vel && play && play.value()._id == 2 && newValue2.x != -1)
            vel.value()._current.x = newValue2.x;
        if (vel && play && play.value()._id == 2 && newValue2.y != -1)
            vel.value()._current.y = newValue2.y;
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
