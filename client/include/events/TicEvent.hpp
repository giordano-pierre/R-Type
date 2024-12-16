/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TicEvent
*/
#pragma once

#include <chrono>

namespace timer = std::chrono;

namespace Rtype::Client {
struct TicEvent {
  TicEvent(const timer::time_point<timer::steady_clock> &time_stamp);
  ~TicEvent() = default;

  timer::time_point<timer::steady_clock> time_stamp;
};
} // namespace Rtype::Client
