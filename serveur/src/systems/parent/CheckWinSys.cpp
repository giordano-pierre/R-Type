/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CheckWinSys
*/

#include "systems/parent/CheckWinSys.hpp"
#include <iostream>

namespace rtype::server {

void CheckWinSys::operator()(ECS &ecs, const TicEvent &,
                             const SparseArray<Tag> &tags,
                             SparseArray<Room> &rooms,
                             SparseArray<Stage> &stages,
                             SparseArray<Child> &children) {
    bool win;
    bool lose;

    for (size_t i = 0; i < tags.size() && i < rooms.size() &&
                       i < stages.size() && i < children.size();
         ++i) {
        const auto &tag = tags[i];
        auto &ro = rooms[i];
        auto &st = stages[i];
        auto &child = children[i];

        if (tag && ro && st && child && ro.value()._state == IN_GAME) {
            win = false;
            lose = true;
            auto subTags = child.value()._ecs_child.get_components<Tag>();

            if (st.value()._enemies.empty())
                win = true;
            for (size_t j = 0; j < subTags.size(); ++j) {
                const auto &subTag = subTags[j];

                if (win && subTag && subTag.value()._type >= ENEMY1 &&
                    subTag.value()._type <= ENEMY6)
                    win = false;
                if (lose && subTag && subTag.value()._type == PLAYER)
                    lose = false;
            }
            // if (st.value()._enemies.empty()) {
            //     win = true;

            //     for (size_t j = 0; j < subTags.size(); ++j) {
            //         const auto &subTag = subTags[j];

            //         if (subTag && subTag.value()._type >= ENEMY1 &&
            //         subTag.value()._type <= ENEMY6) {
            //             win = false;
            //             break;
            //         }
            //     }
            // }
            if (win) {
                std::cout << "WIN !!!" << std::endl;
                child.value()._ecs_child.clean<TicEvent>();
                removeAll(child.value()._ecs_child);
                ro.value()._state = WAITING;
                ro.value()._lastUpdate = 0;
                for (const auto &[uuid, _] : ro.value()._clients_uuid) {
                    RequestEvent event = {SV_GAME_OVER, {}, uuid};
                    ecs.post<RequestEvent>(event);
                    ecs.post<CheckEvent>(
                        {SV_GAME_OVER, tag.value()._id, event});
                }
            }
        }
    }
}

} // namespace rtype::server
