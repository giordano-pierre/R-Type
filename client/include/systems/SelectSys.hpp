/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SelectSys
*/

#pragma once

#include "ECS/ECS.hpp"
#include "events/InputEvent.hpp"
#include "components/Position.hpp"
#include "components/Hitbox.hpp"
#include "components/Drawable.hpp"
#include "components/Selectable.hpp"

namespace Rtype::Client {
    class SelectSys {
        public:
            SelectSys() = default;
            ~SelectSys() = default;

            void operator()(ECS &ecs, const InputEvent &e_input,
                            const SparseArray<Position> &positions,
                            SparseArray<Drawable> &sprites,
                            SparseArray<Hitbox> &hitboxes,
                            SparseArray<Selectable> &selectables);
    };
}
