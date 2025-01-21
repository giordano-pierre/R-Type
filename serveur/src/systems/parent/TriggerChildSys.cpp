/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** TriggerChildSys
*/

#include "systems/parent/TriggerChildSys.hpp"
#include <iostream>

namespace rtype::server {

void TriggerChildSys::operator()(ECS &ecs, const TicEvent &tic_event,
                                 SparseArray<Child> &children) {
    for (size_t i = 0; i < children.size(); ++i) {
        auto &child = children[i];

        if (child) {
            child.value()._ecs_child.post<TicEvent>(tic_event);
            while (!child.value()._ecs_child.empty()) {
                auto evt = child.value()._ecs_child.front();
                evt();
                child.value()._ecs_child.pop_front();
            }
        }
    }
}

} // namespace rtype::server
