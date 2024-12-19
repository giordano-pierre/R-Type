/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** FrameEvent
*/
#include "events/FrameEvent.hpp"

namespace rtype::client {

FrameEvent::FrameEvent(const timer::time_point<timer::steady_clock> &time_stamp)
    : time_stamp(time_stamp) {}

} // namespace rtype::client
