/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** FrameEvent
*/
#pragma once

#include <chrono>

namespace timer = std::chrono;

namespace rtype::client {
struct FrameEvent {
    FrameEvent(const timer::time_point<timer::steady_clock> &time_stamp);
    ~FrameEvent() = default;

    timer::time_point<timer::steady_clock> time_stamp;
};
} // namespace rtype::client
