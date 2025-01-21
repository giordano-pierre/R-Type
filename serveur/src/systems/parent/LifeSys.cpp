/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** LifeSys
*/

#include "systems/parent/LifeSys.hpp"
#include "systems/child/EnemiesSystem.hpp"
#include "systems/child/SpawnQueue.hpp"
#include <iostream>

extern SpawnQueue spawnQueue;
namespace rtype::server {

void LifeSys::operator()(ECS &ecs, const TicEvent &tic_event,
                         SparseArray<Child> &childrens,
                         const SparseArray<Room> &rooms) {
    for (size_t i = 0; i < childrens.size() && i < rooms.size(); ++i) {
        auto &child = childrens[i];
        const auto &ro = rooms[i];

        if (child && ro && ro.value()._state == IN_GAME) {
            auto &subDeads = child.value()._ecs_child.get_components<Dead>();
            auto &subTags = child.value()._ecs_child.get_components<Tag>();

            for (size_t j = 0; j < subDeads.size() && j < subTags.size(); ++j) {
                auto &dead = subDeads[j];
                auto &tag = subTags[j];

                if (dead && tag && dead.value()._isDead) {
                    for (const auto &[uuid, _] : ro.value()._clients_uuid) {
                        // std::cout << "M" << std::endl;
                        ecs.post<RequestEvent>(
                            {SV_KILL_ENTITY, {{"id", tag.value()._id}}, uuid});
                    }
                    // std::cout << "BEFORE KILL" << std::endl;
                    child.value()._ecs_child.kill_entity(
                        child.value()._ecs_child.entity_from_index(j));
                    // std::cout << "AFTER KILL" << std::endl;
                }
            }
        }
    }
}

void LifeSys::operator()(ECS &ecs, const TicEvent &tic_event,
                         SparseArray<Room> &rooms, SparseArray<Stage> &stages,
                         SparseArray<Child> &children) {
    for (size_t i = 0;
         i < rooms.size() && i < stages.size() && i < children.size(); ++i) {
        const auto &ro = rooms[i];
        auto &st = stages[i];
        auto &child = children[i];

        if (ro && st && child && ro.value()._state == IN_GAME) {
            for (int j = 0; j < st.value()._enemies.size(); j++) {
                auto &ennemy = st.value()._enemies[j];
                ennemy.spawn_tic -= 1;
                std::vector<RequestEvent> resp;
                if (ennemy.spawn_tic <= 0) {
                    switch (ennemy.type) {
                    case ENEMY1: {
                        resp =
                            createVFormation(child.value()._ecs_child, ennemy);
                        break;
                    }
                    case ENEMY2: {
                        resp =
                            createSineEnemy(child.value()._ecs_child, ennemy);
                        break;
                    }
                    case ENEMY3: {
                        resp = createChase(child.value()._ecs_child, ennemy);
                        break;
                    }
                    case ENEMY4: {
                        resp = createCharge(child.value()._ecs_child, ennemy);
                        break;
                    }
                    case ENEMY5: {
                        resp = createUpDown(child.value()._ecs_child, ennemy);
                        break;
                    }
                    case BOSS1: {
                        std::cout << "spawning boss" << std::endl;
                        resp = createBoss(child.value()._ecs_child, ennemy);
                        break;
                    }
                    }

                    for (const auto evt : resp) {
                        for (const auto &[uuid, _] : ro.value()._clients_uuid)
                            ecs.post<RequestEvent>(
                                {SV_CREATE_ENTITY, evt.payload, uuid});
                    }
                    st.value()._enemies.erase(st.value()._enemies.begin() + j);
                }
            }
        }
    }
}
} // namespace rtype::server