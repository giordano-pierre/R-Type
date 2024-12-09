/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PressButtonSys
*/

#include "systems/PressButtonSys.hpp"

namespace Rtype::Client {

void PressButtonSys::operator()(ECS &ecs, const InputEvent &e_input,
                SparseArray<Selectable> &selectables)
{
    switch(e_input._event.type) {
        case sf::Event::KeyPressed:
            if (e_input._event.key.code == sf::Keyboard::Space)
                for (size_t i = 0; i < selectables.size(); ++i) {
                    auto &sel = selectables[i];

                    if (sel && sel.value()._isSelected)
                        sel.value()._func(ecs);
                }
            break;
        default:
            return;
    }
}

}
