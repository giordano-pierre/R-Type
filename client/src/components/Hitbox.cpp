/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Hitbox
*/

#include "components/Hitbox.hpp"

namespace Rtype::Client {
  Hitbox::Hitbox(TupleFloat coefSize, bool display, TupleFloat client,
                 TupleFloat server, bool needUpdate)
    : _coefSize(coefSize), _display(display), _client(client), _server(server),
      _needUpdate(needUpdate) {}
}

auto operator<<(std::ostream &out,
                const Rtype::Client::Hitbox &hitbox) -> std::ostream & {
  out << "server: " << hitbox._server.x << " pixel of width and ";
  out << hitbox._server.y << " pixels of height." << std::endl;
  out << "client: " << hitbox._client.x << " pixel of width and ";
  out << hitbox._client.y << " pixels of height.";
  return out;
}
