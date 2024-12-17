/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Velocity
*/

#include "components/Velocity.hpp"

auto operator<<(std::ostream &out,
                const Rtype::Client::Velocity &velocity) -> std::ostream & {
  out << "Velocity: x = " << velocity._current.x
      << ", y = " << velocity._current.y;
  return out;
}
