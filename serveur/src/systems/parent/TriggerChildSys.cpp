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
            std::cout << "TEST move" << std::endl;
            child.value()._ecs_child.get()->post<TicEvent>(tic_event);
            std::cout << "1" << std::endl;
            while (!child.value()._ecs_child.get()->empty()) {
                std::cout << "2" << std::endl;
                auto &evt = child.value()._ecs_child.get()->front();
                std::cout << "3" << std::endl;
                evt();
                std::cout << "4" << std::endl;
                child.value()._ecs_child.get()->pop_front();
                std::cout << "5" << std::endl;
            }
            std::cout << "TEST move finnnnnnnn" << std::endl;
        }
    }
}

} // namespace rtype::server
