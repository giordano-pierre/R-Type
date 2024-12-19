/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** LifeSys
*/

#pragma once

#include "ECS/ECS.hpp"
#include "components/Tag.hpp"
#include "events/CreateEvent.hpp"
#include "events/DeleteEvent.hpp"

namespace rtype::client {
class LifeSys {
  public:
    LifeSys() = default;
    ~LifeSys() = default;

    void operator()(ECS &ecs, const CreationEvent &e_create);
    void operator()(ECS &ecs, const DeleteEvent &e_del, SparseArray<Tag> &tags);
};
} // namespace rtype::client
