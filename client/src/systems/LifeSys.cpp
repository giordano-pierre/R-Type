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
                         SparseArray<Configs> &configs,
                         SparseArray<SFMLObjects> &SFMLObjs,
                         SparseArray<PlayerInfo> &playerInfos,
                         SparseArray<Room> &rooms) {
    auto &myConfig = configs[0].value();
    auto &SFMLObj = SFMLObjs[0].value();
    auto &playerInfo = playerInfos[0].value();
    auto &myRoom = rooms[0].value();

    ecs.clean<FrameEvent>();
    ecs.clean<InputEvent>();
    ecs.clean<TicEvent>();
    switch (e_create._type) {
    case MENU:
        loadMenuSystem(ecs);
        createMenuEntities(ecs, myConfig, SFMLObj);
        break;
    case M_GENERAL:
        loadMenuSystem(ecs);
        createMenuGeneralEntities(ecs, myConfig, SFMLObj);
        break;
    case M_PLAYER:
        loadMenuSystem(ecs);
        createMenuPlayerEntities(ecs, myConfig, SFMLObj);
        break;
    case CUSTOM:
        loadMenuSystem(ecs);
        createCustomEntities(ecs, myConfig, SFMLObj);
        break;
    case M_ROOM:
        loadMenuSystem(ecs);
        createMenuRoomEntities(ecs, e_create._param.value(), myConfig, SFMLObj,
                               playerInfo, myRoom);
        break;
    case M_CONFIG:
        loadMenuSystem(ecs);
        createConfigEntities(ecs, myConfig, SFMLObj);
        break;
    case M_C_GENERAL:
        loadMenuSystem(ecs);
        createConfigGeneralEntites(ecs, myConfig, SFMLObj);
        break;
    case M_C_PLAYER1:
        loadMenuSystem(ecs);
        createConfigPlayer1Entites(ecs, myConfig, SFMLObj);
        break;
    case M_C_PLAYER2:
        loadMenuSystem(ecs);
        createConfigPlayer2Entites(ecs, myConfig, SFMLObj);
        break;
    case GAME:
        loadGameSystem(ecs);
        createGameEntities(ecs, myConfig, SFMLObj);
        break;
    case M_IN_ROOM:
        loadMenuSystem(ecs);
        createMenuInRoomEntities(ecs, myConfig, SFMLObj, myRoom);
        break;
    case MENUROOM:
        loadMenuSystem(ecs);
        createMenuRoomEntities(ecs, myConfig, SFMLObj);
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