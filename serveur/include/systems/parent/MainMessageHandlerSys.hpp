/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** MainMessageHandlerSys
*/

#pragma once

#include "Child.hpp"
#include "Components.hpp"
#include "ECS/ECS.hpp"
#include "events/ReceiveEvent.hpp"
#include "tools.hpp"

namespace rtype::server {

class MainMessageHandlerSys {
  public:
    MainMessageHandlerSys() = default;
    ~MainMessageHandlerSys() = default;

    void operator()(ECS &ecs, const ReceiveEvent &rec_event,
                    SparseArray<Utils> &utils, SparseArray<Room> &rooms,
                    SparseArray<Tag> &tags, SparseArray<Stage> &stages,
                    SparseArray<Child> &children);
};

} // namespace rtype::server
