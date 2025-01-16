/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** UpdateSys
*/

#pragma once

#include "Components.hpp"
#include "ECS/ECS.hpp"
#include "Events.hpp"
#include "Child.hpp"

namespace rtype::server {

class UpdateSys {
  public:
    UpdateSys() = default;
    ~UpdateSys() = default;

    void operator()(ECS &ecs, const UpdateEvent &up_event,
                    SparseArray<Room> &rooms, SparseArray<Child> &children);
};

} // namespace rtype::server
