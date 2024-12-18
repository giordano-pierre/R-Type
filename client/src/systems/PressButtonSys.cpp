/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PressButtonSys
*/

#include "systems/PressButtonSys.hpp"
#include "buttonFunctions.hpp"

namespace Rtype::Client {

void checkLink(ECS &ecs, SparseArray<Pressable> &pressables, Entity ent) {
  if (pressables[ent].value()._link == 0)
    return;
  int currentLink = pressables[ent].value()._link;
  for (size_t i = 0; i < pressables.size(); ++i) {
    auto &myPress = pressables[i];

    if (myPress && myPress.value()._link == currentLink &&
        myPress.value()._isPressed)
      press(ecs, Entity(i));
  }
}

void PressButtonSys::operator()(ECS &ecs, const InputEvent &e_input,
                                const SparseArray<Selectable> &selectables,
                                SparseArray<Pressable> &pressables) {
  switch (e_input._myEvent) {
  case ENTER:
    for (size_t i = 0; i < selectables.size() && i < pressables.size(); ++i) {
      const auto &sel = selectables[i];
      auto &press = pressables[i];

      if (sel && press && sel.value()._isSelected) {
        checkLink(ecs, pressables, Entity(i));
        press.value()._press(ecs, Entity(i));
      }
    }
    break;
  default:
    return;
  }
}

void PressButtonSys::operator()(ECS &ecs, const InputEvent &e_input,
                                const SparseArray<Position> &positions,
                                const SparseArray<Hitbox> &hitboxs,
                                const SparseArray<Selectable> &selectables,
                                SparseArray<Pressable> &pressables) {
  if (e_input._event.type == sf::Event::MouseButtonPressed) {
    for (size_t i = 0; i < selectables.size() && i < positions.size() &&
                       i < hitboxs.size() && i < pressables.size();
         ++i) {
      const auto &sel = selectables[i];
      const auto &pos = positions[i];
      const auto &box = hitboxs[i];
      auto &press = pressables[i];

      if (sel && pos && box && press && sel.value()._isSelected &&
          e_input._event.mouseButton.x >
              pos.value()._client.x - (box.value()._client.x / 2) &&
          e_input._event.mouseButton.x <
              pos.value()._client.x + (box.value()._client.x / 2) &&
          e_input._event.mouseButton.y >
              pos.value()._client.y - (box.value()._client.y / 2) &&
          e_input._event.mouseButton.y <
              pos.value()._client.y + (box.value()._client.y / 2)) {
        checkLink(ecs, pressables, Entity(i));
        press.value()._press(ecs, Entity(i));
      }
    }
  }
}

} // namespace Rtype::Client
