/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Events
*/

#pragma once

#include "events/RequestEvent.hpp"
#include "protocol.hpp"
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

struct CheckEvent {
    CheckEvent(const Protocol &action, const std::string &idr,
               const RequestEvent &req, int time)
        : _action(action), _idr(idr), _request(req), _time(time){};

    const Protocol _action;
    const std::string _idr;
    const RequestEvent _request;
    const int _time;
};

struct UpdateEvent {
    UpdateEvent(const timer::time_point<timer::steady_clock> &time_stamp)
        : time_stamp(time_stamp){};
    ~UpdateEvent() = default;

    timer::time_point<timer::steady_clock> time_stamp;
};

struct PowerupEvent {
    PowerupEvent(float posX, float posY, int type, float dur)
        : _x(posX), _y(posY), _type(type), _duration(dur) {}
    ~PowerupEvent() = default;
    float _x;
    float _y;
    int _type;
    float _duration;
};

} // namespace rtype::server
