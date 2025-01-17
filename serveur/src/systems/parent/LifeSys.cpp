/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** LifeSys
*/

#include "systems/parent/LifeSys.hpp"
#include <iostream>

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
                        std::cout << "M" << std::endl;
                        ecs.post<RequestEvent>(
                            {SV_KILL_ENTITY, {{"id", tag.value()._id}}, uuid});
                    }
                    std::cout << "BEFORE KILL" << std::endl;
                    child.value()._ecs_child.kill_entity(
                        child.value()._ecs_child.entity_from_index(j));
                    std::cout << "AFTER KILL" << std::endl;
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
                if (ennemy.spawn_tic <= 0) {
                    Entity ennemyE = child.value()._ecs_child.spawn_entity();
                    std::string idE = fetch_new_uuid();
                    child.value()._ecs_child.add_component<Tag>(
                        ennemyE, {idE, ennemy.type});
                    child.value()._ecs_child.add_component<Position>(
                        ennemyE, {ennemy.x_pos, ennemy.y_pos});
                    child.value()._ecs_child.add_component<Velocity>(
                        ennemyE, {ennemy.x_velocity, ennemy.y_velocity});
                    child.value()._ecs_child.add_component<HitBox>(
                        ennemyE, {ennemy.x_hitbox, ennemy.y_hitbox});
                    child.value()._ecs_child.add_component<Health>(
                        ennemyE, {ennemy.health});
                    child.value()._ecs_child.add_component<Score>(
                        ennemyE, {ennemy.score});
                    for (const auto &[uuid, _] : ro.value()._clients_uuid)
                        ecs.post<RequestEvent>(
                            {SV_CREATE_ENTITY,
                             {{"id", idE},
                              {"type", ennemy.type},
                              {"pos",
                               {{"x", ennemy.x_pos}, {"y", ennemy.y_pos}}},
                              {"vel",
                               {{"x", ennemy.x_velocity},
                                {"y", ennemy.y_velocity}}},
                              {"hit",
                               {{"x", ennemy.x_hitbox},
                                {"y", ennemy.y_hitbox}}},
                              {"hp", ennemy.health},
                              {"sc", ennemy.score},
                              {"lu", 1}},
                             uuid});
                    st.value()._enemies.erase(st.value()._enemies.begin() + j);
                }
            }
        }
    }
}

} // namespace rtype::server
