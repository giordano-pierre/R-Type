/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** MainMessageHandlerSys
*/

#pragma once

#include "Components.hpp"
#include "ECS/ECS.hpp"
#include "events/ReceiveEvent.hpp"
#include "Child.hpp"

namespace rtype::server {

class MainMessageHandlerSys {
  public:
    MainMessageHandlerSys() = default;
    ~MainMessageHandlerSys() = default;

    void operator()(ECS &ecs, const ReceiveEvent &rec_event,
                    SparseArray<Room> &rooms, SparseArray<Tag> &tags,
                    SparseArray<Child> &children);
};

} // namespace rtype::server
