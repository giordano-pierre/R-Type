/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PressButtonSys
*/

#include "systems/PressButtonSys.hpp"

namespace Rtype::Client {

void PressButtonSys::operator()(ECS &ecs, const InputEvent &e_input,
                                const SparseArray<Position> &positions,
                                const SparseArray<Hitbox> &hitboxs,
                                SparseArray<Selectable> &selectables) {
  switch (e_input._myEvent) {
  case ENTER:
    for (size_t i = 0; i < selectables.size(); ++i) {
      auto &sel = selectables[i];

      if (sel && sel.value()._isSelected)
        sel.value()._func(ecs);
    }
    break;
  default:
    if (e_input._event.type == sf::Event::MouseButtonPressed) {
      for (size_t i = 0;
           i < selectables.size() && i < positions.size() && i < hitboxs.size();
           ++i) {
        auto &sel = selectables[i];
        const auto &pos = positions[i];
        const auto &box = hitboxs[i];

        if (sel && pos && box && sel.value()._isSelected &&
            e_input._event.mouseButton.x >
                pos.value()._client.x - (box.value()._client.x / 2) &&
            e_input._event.mouseButton.x <
                pos.value()._client.x + (box.value()._client.x / 2) &&
            e_input._event.mouseButton.y >
                pos.value()._client.y - (box.value()._client.y / 2) &&
            e_input._event.mouseButton.y <
                pos.value()._client.y + (box.value()._client.y / 2))
          sel.value()._func(ecs);
      }
    }
    break;
  }
}

} // namespace Rtype::Client
