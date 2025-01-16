/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Child
*/

#include "Child.hpp"

namespace rtype::server {

void loadSubSystem(Child &child) {
    child._ecs_child.subscribe<TicEvent, Position, Velocity>(child._moveSys);
    child._ecs_child.subscribe<TicEvent, Health>(child._hpSys);
    child._ecs_child.subscribe<TicEvent, Position, HitBox, Tag, Health, Owner, Score>(child._collSys);
    child._ecs_child.subscribe<TicEvent, Position, Tag, HitBox>(child._collSys);
}

}
