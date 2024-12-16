/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position
*/

#include "components/Position.hpp"

auto operator<<(std::ostream &out, const Rtype::Client::Position &position)
    -> std::ostream & {
  out << "client: x = " << position._client.x << ", y = " << position._client.y
      << std::endl;
  out << "server: x = " << position._server.x << ", y = " << position._server.y;
  return out;
}
