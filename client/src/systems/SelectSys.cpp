/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SelectSys
*/

#include "systems/SelectSys.hpp"

namespace rtype::client {

void changeSelect(ECS &ecs, SparseArray<Selectable> &selectables,
                  size_t newSelect, size_t oldSelect = -1) {
    if (newSelect != oldSelect) {
        selectables[newSelect].value()._isSelected = true;
        selectables[newSelect].value()._sel(ecs, Entity(newSelect));
    }
    if (oldSelect != -1) {
        selectables[oldSelect].value()._isSelected = false;
        selectables[oldSelect].value()._desel(ecs, Entity(oldSelect));
    }
}

void compareDist(const TupleFloat oldPos, const TupleFloat objPos,
                 size_t objInd, float &dist, size_t &newEntity,
                 bool &isNewEntity) {
    float tmp = computeDist(oldPos, objPos);
    if (tmp < dist || dist == -1) {
        dist = tmp;
        newEntity = objInd;
        isNewEntity = true;
    }
}

void SelectSys::operator()(ECS &ecs, const InputEvent &e_input,
                           const SparseArray<Position> &positions,
                           SparseArray<Drawable> &sprites,
                           SparseArray<Selectable> &selectables) {
    bool isOldEntity = false;
    size_t oldEntity = -1;
    TupleFloat oldPos;
    bool isNewEntity = false;
    size_t newEntity;
    float dist = -1;

    if (e_input._event.type != sf::Event::KeyPressed)
        return;

    for (size_t i = 0; i < positions.size() && i < selectables.size(); ++i) {
        const auto &pos = positions[i];
        const auto &sel = selectables[i];

        if (!pos || !sel)
            continue;
        if (sel.value()._isSelected) {
            oldEntity = i;
            oldPos = pos.value()._client;
            isOldEntity = true;
        }
    }

    if (!isOldEntity) {
        if (e_input._myEvent == UP1P || e_input._myEvent == DOWN1P ||
            e_input._myEvent == LEFT1P || e_input._myEvent == RIGHT1P) {
            for (size_t i = 0; i < selectables.size(); ++i) {
                auto &sel = selectables[i];

                if (sel) {
                    changeSelect(ecs, selectables, i);
                    return;
                }
            }
            return;
        }
    }

    for (size_t i = 0;
         i < positions.size() && i < sprites.size() && i < selectables.size();
         ++i) {
        const auto &pos = positions[i];
        auto &sprite = sprites[i];
        auto &sel = selectables[i];

        if (!pos || !sprite || !sel)
            continue;
        if (sel.value()._isSelected)
            continue;
        switch (e_input._myEvent) {
        case UP1P:
            if (oldPos.y > pos.value()._client.y)
                compareDist(oldPos, pos.value()._client, i, dist, newEntity,
                            isNewEntity);
            break;
        case DOWN1P:
            if (oldPos.y < pos.value()._client.y)
                compareDist(oldPos, pos.value()._client, i, dist, newEntity,
                            isNewEntity);
            break;
        case LEFT1P:
            if (oldPos.x > pos.value()._client.x)
                compareDist(oldPos, pos.value()._client, i, dist, newEntity,
                            isNewEntity);
            break;
        case RIGHT1P:
            if (oldPos.x < pos.value()._client.x)
                compareDist(oldPos, pos.value()._client, i, dist, newEntity,
                            isNewEntity);
            break;
        default:
            break;
        }
    }

    if (isNewEntity)
        changeSelect(ecs, selectables, newEntity, oldEntity);
}

void SelectSys::operator()(ECS &ecs, const InputEvent &e_input,
                           const SparseArray<Position> &positions,
                           SparseArray<Drawable> &sprites,
                           SparseArray<Hitbox> &hitboxes,
                           SparseArray<Selectable> &selectables) {
    bool isOldEntity = false;
    size_t oldEntity = -1;
    TupleFloat oldPos;
    bool isNewEntity = false;
    size_t newEntity;
    float dist = -1;

    if (e_input._event.type != sf::Event::MouseMoved)
        return;

    for (size_t i = 0; i < positions.size() && i < selectables.size(); ++i) {
        const auto &pos = positions[i];
        const auto &sel = selectables[i];

        if (!pos || !sel)
            continue;
        if (sel.value()._isSelected) {
            oldEntity = i;
            oldPos = pos.value()._client;
            isOldEntity = true;
        }
    }

    for (size_t i = 0; i < positions.size() && i < sprites.size() &&
                       i < selectables.size() && i < hitboxes.size();
         ++i) {
        const auto &pos = positions[i];
        auto &sprite = sprites[i];
        auto &sel = selectables[i];
        auto &box = hitboxes[i];

        if (!pos || !sprite || !sel || !box)
            continue;
        if (sel.value()._isSelected)
            continue;
        switch (e_input._event.type) {
        case sf::Event::MouseMoved:
            if (e_input._event.mouseMove.x >
                    pos.value()._client.x - (box.value()._client.x / 2) &&
                e_input._event.mouseMove.x <
                    pos.value()._client.x + (box.value()._client.x / 2) &&
                e_input._event.mouseMove.y >
                    pos.value()._client.y - (box.value()._client.y / 2) &&
                e_input._event.mouseMove.y <
                    pos.value()._client.y + (box.value()._client.y / 2))
                changeSelect(ecs, selectables, i, oldEntity);
            break;
        default:
            break;
        }
    }

    if (isNewEntity)
        changeSelect(ecs, selectables, newEntity, oldEntity);
}

} // namespace rtype::client
