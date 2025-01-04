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

void LifeSys::operator()(ECS &ecs, const CreationEvent &e_create,
                         SparseArray<Window> &windows) {
    auto &myWindow = windows[0].value();

    ecs.clean<FrameEvent>();
    ecs.clean<InputEvent>();
    ecs.clean<TicEvent>();
    switch (e_create._type) {
    case MENU:
        loadMenuSystem(ecs);
        createMenuEntities(ecs, myWindow);
        break;
    case M_GENERAL:
        loadMenuSystem(ecs);
        createMenuGeneralEntities(ecs, myWindow);
        break;
    case M_PLAYER:
        loadMenuSystem(ecs);
        createMenuPlayerEntities(ecs, myWindow);
        break;
    case M_CONFIG:
        loadMenuSystem(ecs);
        createConfigEntities(ecs, myWindow);
        break;
    case M_C_GENERAL:
        loadMenuSystem(ecs);
        createConfigGeneralEntites(ecs, myWindow);
        break;
    case M_C_PLAYER1:
        loadMenuSystem(ecs);
        createConfigPlayer1Entites(ecs, myWindow);
        break;
    case M_C_PLAYER2:
        loadMenuSystem(ecs);
        createConfigPlayer2Entites(ecs, myWindow);
        break;
    case GAME:
        loadGameSystem(ecs);
        createGameEntities(ecs, myWindow);
        break;
    default:
        return;
    }
}

void LifeSys::operator()(ECS &ecs, const DeleteEvent &e_del,
                         SparseArray<Scene> &scenes) {
    for (size_t i = 0; i < scenes.size(); ++i) {
        auto &sce = scenes[i];

        if (sce && sce.value()._type == e_del._type) {
            ecs.kill_entity(Entity(i));
        }
    }
}
} // namespace rtype::client
