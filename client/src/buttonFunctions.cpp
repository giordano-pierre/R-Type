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

void press(ECS &ecs, Entity i) {
  auto &press = ecs.get_components<Pressable>();
  auto &draw = ecs.get_components<Drawable>();

  if (i < press.size() && press[i] && i < draw.size() && draw[i]) {
    if (!press[i].value()._isPressed)
      draw[i].value()._sprite.setTexture(*press[i].value()._texture);
    else
      draw[i].value()._sprite.setTexture(*draw[i].value()._texture);
    press[i].value()._isPressed = !press[i].value()._isPressed;
  }
}

} // namespace Rtype::Client
