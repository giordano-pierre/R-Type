/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** buttonFunctions
*/

#include "ECS/ECS.hpp"
#include "ecsObjects.hpp"
#include <iostream>

namespace Rtype::Client {

void select(ECS &ecs, Entity i) {
  auto &sel = ecs.get_components<Selectable>();

  if (i < sel.size() && sel[i]) {
    sel[i].value()._display = true;
  }
}

void deselect(ECS &ecs, Entity i) {
  auto &sel = ecs.get_components<Selectable>();

  if (i < sel.size() && sel[i]) {
    sel[i].value()._display = false;
  }
}

} // namespace Rtype::Client
