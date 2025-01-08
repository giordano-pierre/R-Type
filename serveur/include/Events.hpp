/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Events
*/

#pragma once

#include <chrono>
#include <string>

namespace timer = std::chrono;

namespace rtype::server {

struct TicEvent {
    TicEvent(const timer::time_point<timer::steady_clock> &time_stamp)
        : time_stamp(time_stamp){};
    ~TicEvent() = default;

    timer::time_point<timer::steady_clock> time_stamp;
};

struct RemoveClient {
    RemoveClient(const std::string &uuid) : _uuid(uuid) {}
    ~RemoveClient() = default;

    std::string _uuid;
};

}
