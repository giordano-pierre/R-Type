/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SelectSys
*/

#include "systems/SelectSys.hpp"

#include <iostream>

namespace Rtype::Client {

void changeSelect(SparseArray<Drawable> &sprites,
                  SparseArray<Hitbox> &hitboxes,
                  SparseArray<Selectable> &selectables,
                  size_t newSelect, size_t oldSelect = -1)
{
    if (newSelect != oldSelect) {
        selectables[newSelect].value()._isSelected = true;
        sprites[newSelect].value()._sprite.setTexture(*selectables[newSelect].value()._texture);
        hitboxes[newSelect].value()._coefSize.x += 0.01;
        hitboxes[newSelect].value()._coefSize.y += 0.005625;
        hitboxes[newSelect].value()._needUpdate = true;
    }
    if (oldSelect != -1) {
        selectables[oldSelect].value()._isSelected = false;
        sprites[oldSelect].value()._sprite.setTexture(*sprites[oldSelect].value()._texture);
        hitboxes[oldSelect].value()._coefSize.x -= 0.01;
        hitboxes[oldSelect].value()._coefSize.y -= 0.005625;
        hitboxes[oldSelect].value()._needUpdate = true;
    }
}

void compareDist(const TupleFloat oldPos, const TupleFloat objPos, size_t objInd,
                 float &dist, size_t &newEntity, bool &isNewEntity)
{
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
                           SparseArray<Hitbox> &hitboxes,
                           SparseArray<Selectable> &selectables)
{
    bool isOldEntity = false;
    size_t oldEntity = -1;
    TupleFloat oldPos;
    bool isNewEntity = false;
    size_t newEntity;
    float dist = -1;

    if (e_input._event.type != sf::Event::KeyPressed && e_input._event.type != sf::Event::MouseMoved)
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
        if (e_input._event.type == sf::Event::KeyPressed && (
            e_input._myEvent == UP ||
            e_input._myEvent == DOWN ||
            e_input._myEvent == LEFT ||
            e_input._myEvent == RIGHT)) {
            for (size_t i = 0; i < sprites.size() && i < selectables.size() && i < hitboxes.size(); ++i) {
                auto &sprite = sprites[i];
                auto &sel = selectables[i];
                auto &box = hitboxes[i];

                if (sprite && sel && box) {
                    changeSelect(sprites, hitboxes, selectables, i);
                    return;
                }
            }
            return;
        }
    }

    for (size_t i = 0; i < positions.size() && i < sprites.size() && i < selectables.size() && i < hitboxes.size(); ++i) {
        const auto &pos = positions[i];
        auto &sprite = sprites[i];
        auto &sel = selectables[i];
        auto &box = hitboxes[i];

        if (!pos || !sprite || !sel || !box)
            continue;
        if (sel.value()._isSelected)
            continue;
        switch (e_input._event.type) {
            case sf::Event::KeyPressed:
                if (e_input._myEvent == UP && oldPos.y > pos.value()._client.y)
                    compareDist(oldPos, pos.value()._client, i, dist, newEntity, isNewEntity);
                if (e_input._myEvent == DOWN && oldPos.y < pos.value()._client.y)
                    compareDist(oldPos, pos.value()._client, i, dist, newEntity, isNewEntity);
                if (e_input._myEvent == LEFT && oldPos.x > pos.value()._client.x)
                    compareDist(oldPos, pos.value()._client, i, dist, newEntity, isNewEntity);
                if (e_input._myEvent == RIGHT && oldPos.x < pos.value()._client.x)
                    compareDist(oldPos, pos.value()._client, i, dist, newEntity, isNewEntity);
                break;
            case sf::Event::MouseMoved:
                if (e_input._event.mouseMove.x > pos.value()._client.x - (box.value()._client.x / 2) &&
                    e_input._event.mouseMove.x < pos.value()._client.x + (box.value()._client.x / 2) &&
                    e_input._event.mouseMove.y > pos.value()._client.y - (box.value()._client.y / 2) &&
                    e_input._event.mouseMove.y < pos.value()._client.y + (box.value()._client.y / 2))
                        changeSelect(sprites, hitboxes, selectables, i, oldEntity);
                break;
            default:
                return;
        }
    }

    if (isNewEntity)
        changeSelect(sprites, hitboxes, selectables, newEntity, oldEntity);
}

}
