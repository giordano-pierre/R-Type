/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CheatSys
*/

#include "systems/CheatSys.hpp"

namespace Rtype::Client {

void CheatSys::operator()(ECS &ecs, const InputEvent &e_input,
                          SparseArray<Window> &window) {
  bool changeState = false;

  if (e_input._myEvent != NOTHING)
    return;
  switch (e_input._event.type) {
  case sf::Event::KeyPressed:
    if (e_input._event.key.code == sf::Keyboard::H)
      changeState = true;
    break;
  default:
    return;
  }

  if (changeState)
    window[0].value()._displayHitboxs = !window[0].value()._displayHitboxs;
}

} // namespace Rtype::Client
