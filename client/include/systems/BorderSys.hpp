/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** BorderSys
*/

#pragma once

#include "ECS/ECS.hpp"
#include "events/TicEvent.hpp"
#include "components/Window.hpp"
#include "components/Tag.hpp"
#include "components/Hitbox.hpp"
#include "components/Position.hpp"
#include "components/Type.hpp"
#include "components/Window.hpp"
#include "events/TicEvent.hpp"

namespace Rtype::Client {
class BorderSys {
public:
  BorderSys() = default;
  ~BorderSys() = default;

        void operator()(ECS &ecs, const TicEvent &e_tic,
                        const SparseArray<Window> &windows,
                        const SparseArray<Tag> &tags,
                        const SparseArray<Hitbox> &hitboxs,
                        SparseArray<Position> &positions);
    };
}
