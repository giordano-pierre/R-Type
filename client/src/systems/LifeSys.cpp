/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** LifeSys
*/

#include "systems/LifeSys.hpp"
#include "createEntities.hpp"

namespace Rtype::Client {

void LifeSys::operator()(ECS &ecs, const CreateEvent &e_create) {
  switch (e_create._type) {
  case MENU:
    createMenuEntities(ecs);
    break;
  case CONFIG:
    createConfigEntities(ecs);
    break;
  case CGENERAL:
    break;
  case CPLAYER:
    createConfigPlayer1Entites(ecs);
    break;
  default:
    createGameEntities(ecs);
    return;
  }
}

void LifeSys::operator()(ECS &ecs, const DeleteEvent &e_del,
                         SparseArray<Tag> &tags) {
  for (size_t i = 0; i < tags.size(); ++i) {
    auto &tag = tags[i];

    if (tag && tag.value()._type == e_del._type) {
      ecs.kill_entity(Entity(i));
    }
  }
}
} // namespace Rtype::Client
