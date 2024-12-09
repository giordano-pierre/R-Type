/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SelectSys
*/

#include "systems/SelectSys.hpp"

#include <iostream>

namespace Rtype::Client {

void SelectSys::operator()(ECS &ecs, const InputEvent &e_input,
                           const SparseArray<Position> &positions,
                           SparseArray<Drawable> &sprites,
                           SparseArray<Hitbox> &hitboxes,
                           SparseArray<Selectable> &selectables)
{
    bool isCurrentEntity = false;
    size_t currentEntity;
    TupleFloat currentPos;
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
            currentEntity = i;
            currentPos = pos.value()._current;
            isCurrentEntity = true;
        }
    }

    if (!isCurrentEntity  && (e_input._event.key.code == sf::Keyboard::Up ||
                              e_input._event.key.code == sf::Keyboard::Down ||
                              e_input._event.key.code == sf::Keyboard::Left ||
                              e_input._event.key.code == sf::Keyboard::Right)) {
        for (size_t i = 0; i < sprites.size() && i < selectables.size() && i < hitboxes.size(); ++i) {
            auto &sprite = sprites[i];
            auto &sel = selectables[i];
            auto &box = hitboxes[i];

            if (sprite && sel && box) {
                sel.value()._isSelected = true;
                sprite.value()._sprite.setTexture(*sel.value()._texture);
                box.value()._coefSize.x += 0.01;
                box.value()._coefSize.y += 0.005625;
                return;
            }
        }
        return;
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
        switch (e_input._event.key.code) {
            case sf::Keyboard::Up:
                if (currentPos.y > pos.value()._current.y) {
                    float tmp = computeDist(currentPos, pos.value()._current);
                    if (tmp < dist || dist == -1) {
                        dist = tmp;
                        newEntity = i;
                        isNewEntity = true;
                    }
                }
                break;
            case sf::Keyboard::Down:
                if (currentPos.y < pos.value()._current.y) {
                    float tmp = computeDist(currentPos, pos.value()._current);
                    if (tmp < dist || dist == -1) {
                        dist = tmp;
                        newEntity = i;
                        isNewEntity = true;
                    }
                }
                break;
            case sf::Keyboard::Left:
                if (currentPos.x > pos.value()._current.x) {
                    float tmp = computeDist(currentPos, pos.value()._current);
                    if (tmp < dist || dist == -1) {
                        dist = tmp;
                        newEntity = i;
                        isNewEntity = true;
                    }
                }
                break;
            case sf::Keyboard::Right:
                if (currentPos.x < pos.value()._current.x) {
                    float tmp = computeDist(currentPos, pos.value()._current);
                    if (tmp < dist || dist == -1) {
                        dist = tmp;
                        newEntity = i;
                        isNewEntity = true;
                    }
                }
                break;
            default:
                break;
        }
    }

    if (isNewEntity) {
        selectables[currentEntity].value()._isSelected = false;
        selectables[newEntity].value()._isSelected = true;
        sprites[currentEntity].value()._sprite.setTexture(*sprites[currentEntity].value()._texture);
        sprites[newEntity].value()._sprite.setTexture(*selectables[newEntity].value()._texture);
        hitboxes[currentEntity].value()._coefSize.x -= 0.01;
        hitboxes[currentEntity].value()._coefSize.y -= 0.005625;
        hitboxes[newEntity].value()._coefSize.x += 0.01;
        hitboxes[newEntity].value()._coefSize.y += 0.005625;
    }
}

}
