/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** FireRateSys
*/

#pragma once

#include "ECS/ECS.hpp"
#include "components/Playable.hpp"
#include "events/TicEvent.hpp"

namespace rtype::client {

class FireRateSys {
  public:
    FireRateSys() = default;
    ~FireRateSys() = default;

    void operator()(ECS &ecs, const TicEvent &e_tic,
                    SparseArray<Playable> &players);
};

} // namespace rtype::client
