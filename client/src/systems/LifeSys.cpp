/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** LifeSys
*/

#include "systems/LifeSys.hpp"
#include "createEntities.hpp"
#include "events/FrameEvent.hpp"
#include "events/InputEvent.hpp"
#include "events/TicEvent.hpp"
#include "loadSystems.hpp"

namespace rtype::client {

void LifeSys::operator()(ECS &ecs, const CreationEvent &e_create) {
    ecs.clean<FrameEvent>();
    ecs.clean<InputEvent>();
    ecs.clean<TicEvent>();
    switch (e_create._type) {
    case MENU:
        loadMenuSystem(ecs);
        createMenuEntities(ecs);
        break;
    case CONFIG:
        loadMenuSystem(ecs);
        createConfigEntities(ecs);
        break;
    case CGENERAL:
        loadMenuSystem(ecs);
        createConfigGeneralEntites(ecs);
        break;
    case CPLAYER1:
        loadMenuSystem(ecs);
        createConfigPlayer1Entites(ecs);
        break;
    case CPLAYER2:
        loadMenuSystem(ecs);
        createConfigPlayer2Entites(ecs);
        break;
    default:
        loadGameSystem(ecs);
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
} // namespace rtype::client
