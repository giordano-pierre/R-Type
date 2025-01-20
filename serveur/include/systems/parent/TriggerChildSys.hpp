/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** TriggerChildSys
*/

#pragma once

#include "Child.hpp"
#include "Components.hpp"
#include "ECS/ECS.hpp"
#include "Events.hpp"

namespace rtype::server {

class TriggerChildSys {
  public:
    TriggerChildSys() = default;
    ~TriggerChildSys() = default;

    void operator()(ECS &ecs, const TicEvent &tic_event,
                    SparseArray<Child> &children);
};

} // namespace rtype::server
