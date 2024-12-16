/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** tools
*/

#include <cmath>

#include "tools.hpp"

namespace Rtype::Client {

float computeDist(TupleFloat a, TupleFloat b) {
  return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

} // namespace Rtype::Client
