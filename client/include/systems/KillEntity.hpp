/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** KillEntity
*/

#pragma once

#include "ECS/ECS.hpp"
#include "components/LastUpdate.hpp"
#include "events/TicEvent.hpp"

namespace rtype::client {

class KillEntity {
  public:
    KillEntity() = default;
    ~KillEntity() = default;

    void operator()(ECS &ecs, const TicEvent &,
                    SparseArray<LastUpdate> &lastups);
};

} // namespace rtype::client
