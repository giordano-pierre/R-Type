/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** BorderSys
*/

#pragma once

#include "ECS/ECS.hpp"
#include "components/Configs.hpp"
#include "components/Hitbox.hpp"
#include "components/Position.hpp"
#include "components/Tag.hpp"
#include "events/TicEvent.hpp"

namespace rtype::client {
class BorderSys {
  public:
    BorderSys() = default;
    ~BorderSys() = default;

    void operator()(ECS &ecs, const TicEvent &e_tic,
                    const SparseArray<Configs> &configs,
                    const SparseArray<Tag> &tags,
                    const SparseArray<Hitbox> &hitboxs,
                    SparseArray<Position> &positions);
};
} // namespace rtype::client
