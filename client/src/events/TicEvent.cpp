/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TicEvent
*/
#include "events/TicEvent.hpp"

namespace Rtype::Client {

TicEvent::TicEvent(const timer::time_point<timer::steady_clock> &time_stamp)
    : time_stamp(time_stamp) {}

} // namespace Rtype::Client
