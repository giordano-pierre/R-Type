/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** TriggerChildSys
*/

#pragma once

#include "ECS/ECS.hpp"
#include "Events.hpp"
#include "Components.hpp"

namespace rtype::server {

class TriggerChildSys {
    public:
        TriggerChildSys() = default;
        ~TriggerChildSys() = default;

        void operator()(ECS &ecs, const TicEvent &tic_event, SparseArray<Child> &children);
};

}
