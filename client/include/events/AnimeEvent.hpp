/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AnimeEvent
*/

#pragma once

#include <chrono>

namespace timer = std::chrono;

namespace Rtype::Client {
struct AnimeEvent {
    AnimeEvent(const timer::time_point<timer::steady_clock> &time_stamp)
        : time_stamp(time_stamp) {};
    ~AnimeEvent() = default;

    timer::time_point<timer::steady_clock> time_stamp;
};
} // namespace Rtype::Client
