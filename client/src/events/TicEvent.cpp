/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TicEvent
*/
#include "events/TicEvent.hpp"

namespace rtype::client {

TicEvent::TicEvent(const timer::time_point<timer::steady_clock> &time_stamp)
    : time_stamp(time_stamp) {}

} // namespace rtype::client
