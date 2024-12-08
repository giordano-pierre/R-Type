/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** BorderSys
*/

#include "systems/BorderSys.hpp"
#include "tools.hpp"
#include <iostream>

namespace Rtype::Client {

void BorderSys::operator()(ECS &ecs, const TicEvent &e_tic,
                        const SparseArray<Window> &windows,
                        const SparseArray<Type> &types,
                        const SparseArray<Hitbox> &hitboxs,
                        SparseArray<Position> &positions)
{
    TupleUInt sizeWindow = (windows.size() > 0 && windows[0]) ? windows[0].value()._size : (TupleUInt){1920, 1080};

    for (size_t i = 0; i < types.size() && i < hitboxs.size() && i < positions.size(); ++i) {
        const auto &type = types[i];
        const auto &box = hitboxs[i];
        auto &pos = positions[i];

        if (!type || !box || !pos)
            continue;
        TupleFloat sizeObj = {box.value()._coefSize.x * sizeWindow.x / 2, box.value()._coefSize.y * sizeWindow.y / 2};
        switch (type.value()._type) {
            case BACKGROUND:
                if (pos.value()._current.x + sizeObj.x < 0)
                    pos.value()._current.x += sizeObj.x * 4;
                break;
            case PLAYER:
                if (pos.value()._current.x - sizeObj.x < 0)
                    pos.value()._current.x = sizeObj.x;
                if (pos.value()._current.x + sizeObj.x > sizeWindow.x)
                    pos.value()._current.x = sizeWindow.x - sizeObj.x;
                if (pos.value()._current.y - sizeObj.y < 0)
                    pos.value()._current.y = sizeObj.y;
                if (pos.value()._current.y + sizeObj.y > sizeWindow.y)
                    pos.value()._current.y = sizeWindow.y - sizeObj.y;
                break;
            case SHOT:
                if (pos.value()._current.x - sizeObj.x > sizeWindow.x)
                    ecs.kill_entity(Entity(i));
                break;
            default:
                break;
        }

    }
}

}
