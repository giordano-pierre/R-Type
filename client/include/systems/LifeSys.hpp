/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** LifeSys
*/

#pragma once

#include "ECS/ECS.hpp"
#include "components/Configs.hpp"
#include "components/PlayerInfo.hpp"
#include "components/Room.hpp"
#include "components/SFMLObjects.hpp"
#include "components/Scene.hpp"
#include "events/CreateEvent.hpp"
#include "events/DeleteEvent.hpp"

namespace rtype::client {
class LifeSys {
  public:
    LifeSys() = default;
    ~LifeSys() = default;

    void operator()(ECS &ecs, const CreationEvent &e_create,
                    SparseArray<Configs> &configs,
                    SparseArray<SFMLObjects> &SFMLObjs,
                    SparseArray<PlayerInfo> &playerInfo,
                    SparseArray<Room> &rooms);
    void operator()(ECS &ecs, const DeleteEvent &e_del,
                    SparseArray<Scene> &scenes);
};
} // namespace rtype::client
