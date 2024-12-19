/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** FrameSys
*/

#pragma once

#include "ECS/ECS.hpp"
#include "components/Drawable.hpp"
#include "events/AnimeEvent.hpp"

namespace rtype::client {
class FrameSys {
  public:
    FrameSys() = default;
    ~FrameSys() = default;

    void operator()(ECS &ecs, const AnimeEvent &,
                    SparseArray<Drawable> &sprites);
};
} // namespace rtype::client
