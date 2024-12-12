/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Type
*/

#include "components/Type.hpp"

std::ostream &operator<<(std::ostream &out, const Rtype::Client::Type &type) {
  switch (type._type) {
  case Rtype::Client::BACKGROUND:
    out << "Is a Background";
    break;
  case Rtype::Client::PLAYER:
    out << "Is a Player";
    break;
  case Rtype::Client::SHOT:
    out << "Is a Shot";
    break;
  default:
    break;
  }
  return out;
}
