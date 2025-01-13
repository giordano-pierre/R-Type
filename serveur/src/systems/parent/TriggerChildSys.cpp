/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** TriggerChildSys
*/

#include "systems/parent/TriggerChildSys.hpp"

namespace rtype::server {

void TriggerChildSys::operator()(ECS &ecs, const TicEvent &tic_event,
                                 SparseArray<Child> &children) {
    for (size_t i = 0; i < children.size(); ++i) {
        auto &child = children[i];

        if (child) {
            child.value()._ecs_child.post<TicEvent>(tic_event);
        }
    }
}

} // namespace rtype::server
