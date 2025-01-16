/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** SubMessageHandlerSys
*/

#include "systems/child/SubMessageHandlerSys.hpp"
#include <iostream>

namespace rtype::server {

void movePlayer(ECS &ecs, const ReceiveEvent &rec_event,
                const SparseArray<Tag> &tags,
                SparseArray<Velocity> &velocities) {
    // std::cout << "TEST_sub move" << std::endl;
    auto input = rec_event.payload["e_type"].get<std::string>();
    auto idp = rec_event.payload["idp"].get<std::string>();

    for (size_t i = 0; i < tags.size() && i < velocities.size(); ++i) {
        const auto &tag = tags[i];
        auto &vel = velocities[i];

        if (tag && vel && tag.value()._id == idp) {
            if (input == "up")
                vel.value().y = -8;
            if (input == "down")
                vel.value().y = 8;
            if (input == "right")
                vel.value().x = 8;
            if (input == "left")
                vel.value().x = -8;
            if (input == "releasedX")
                vel.value().x = 0;
            if (input == "releasedY")
                vel.value().y = 0;
        }
    }
    // std::cout << "TEST_sub move FINNNNNNNNNNNNNNNNN" << std::endl;
}

void SubMessageHandlerSys::operator()(ECS &ecs, const ReceiveEvent &rec_event,
                                      const SparseArray<Tag> &tags,
                                      SparseArray<Velocity> &velocities) {
    // std::cout << "MESS" << std::endl;
    switch (rec_event.action) {
    case CL_MOVE: {
        movePlayer(ecs, rec_event, tags, velocities);
        break;
    }
    default:
        break;
    }
    // std::cout << "FINNNNNNNNNN MESS" << std::endl;
}

} // namespace rtype::server
