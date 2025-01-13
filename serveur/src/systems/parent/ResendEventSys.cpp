/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** ResendEventSys
*/

#include "systems/parent/ResendEventSys.hpp"
#include "events/ReceiveEvent.hpp"
#include "events/RequestEvent.hpp"

namespace rtype::server {

void ResendEventSys::operator()(ECS &ecs, const CheckEvent &check_event,
                                const SparseArray<Room> &rooms,
                                const SparseArray<Tag> &tags)
{
    StateGame target;

    switch (check_event._action) {
        case LAUNCH_GAME:
            target = IN_GAME;
            break;
        case PAUSE_GAME:
            if (check_event._request.payload["state"].get<std::string>() == "on") {
                target = IN_PAUSE;
            } else {
                target = IN_GAME;
            }
        case SV_GAME_OVER:
            target = WAITING;
        default:
            return;
    }

    for (size_t i = 0; i < tags.size() && i < rooms.size(); ++i) {
        const auto &tag = tags[i];
        const auto &ro = rooms[i];

        if (ro && tag && tag.value()._id == check_event._idr) {
            auto client_it = ro.value()._clients_uuid.find(check_event._request.receiver_uuid);
            if (client_it == ro.value()._clients_uuid.end())
                break;;
            if (client_it->second != target) {
                ecs.post<RequestEvent>(check_event._request);
                ecs.post<CheckEvent>(check_event);
                break;
            }
        }
    }        
}

}
