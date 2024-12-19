/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** BorderSys
*/

#include "systems/BorderSys.hpp"
#include "tools.hpp"

namespace rtype::client {

void BorderSys::operator()(ECS &ecs, const TicEvent &e_tic,
                           const SparseArray<Window> &windows,
                           const SparseArray<Tag> &tags,
                           const SparseArray<Hitbox> &hitboxs,
                           SparseArray<Position> &positions) {
    TupleUInt serverSize = (windows.size() > 0 && windows[0])
                               ? windows[0].value()._serverSize
                               : (TupleUInt){1920, 1080};

    for (size_t i = 0;
         i < tags.size() && i < hitboxs.size() && i < positions.size(); ++i) {
        const auto &tag = tags[i];
        const auto &box = hitboxs[i];
        auto &pos = positions[i];

        if (!tag || !box || !pos)
            continue;
        TupleFloat sizeObj = {box.value()._server.x / 2,
                              box.value()._server.y / 2};
        switch (tag.value()._type) {
        case BACKGROUND:
            if (pos.value()._server.x + sizeObj.x < 0) {
                pos.value()._server.x += sizeObj.x * 4;
                pos.value()._needUpdate = true;
            }
            break;
        case PLAYER:
            if (pos.value()._server.x - sizeObj.x < 0) {
                pos.value()._server.x = sizeObj.x;
                pos.value()._needUpdate = true;
            }
            if (pos.value()._server.x + sizeObj.x > serverSize.x) {
                pos.value()._server.x = serverSize.x - sizeObj.x;
                pos.value()._needUpdate = true;
            }
            if (pos.value()._server.y - sizeObj.y < 0) {
                pos.value()._server.y = sizeObj.y;
                pos.value()._needUpdate = true;
            }
            if (pos.value()._server.y + sizeObj.y > serverSize.y) {
                pos.value()._server.y = serverSize.y - sizeObj.y;
                pos.value()._needUpdate = true;
            }
            break;
        case SHOT:
            if (pos.value()._server.x - sizeObj.x > serverSize.x ||
                pos.value()._server.x + sizeObj.x < 0 ||
                pos.value()._server.y - sizeObj.y > serverSize.y ||
                pos.value()._server.y + sizeObj.y < 0)
                ecs.kill_entity(Entity(i));
            break;
        default:
            break;
        }
    }
}

} // namespace rtype::client
