/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** DrawableSys
*/

#pragma once

#include "ECS/ECS.hpp"
#include "events/FrameEvent.hpp"
#include "events/InputEvent.hpp"
#include "components/Drawable.hpp"

namespace Rtype::Client {
    class DrawableSys {
        public:
            DrawableSys() = default;
            ~DrawableSys() = default;

            void operator()(ECS &ecs, const FrameEvent &,
                            SparseArray<Drawable> &sprites);

            void operator()(ECS &ecs, const InputEvent &e_input,
                            SparseArray<Drawable> &sprites);
    };
}
