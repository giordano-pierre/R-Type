/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** FrameSys
*/

#pragma once

#include "ECS/ECS.hpp"
#include "events/FrameEvent.hpp"
#include "events/InputEvent.hpp"
#include "components/Drawable.hpp"

namespace Rtype::Client {
    class FrameSys {
        public:
            FrameSys() = default;
            ~FrameSys() = default;

            void operator()(ECS &ecs, const FrameEvent &,
                            SparseArray<Drawable> &sprites);

            // void operator()(ECS &ecs, const InputEvent &e_input,
            //                 SparseArray<Drawable> &sprites);
    };
}
