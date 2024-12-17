/*
** EPITECH PROJECT, 2024
** piscine
** File description:
** ECS.inl
*/

#include "ECS/ECS.hpp"

ECS::ECS() { _nb_entities = 0; }

auto ECS::front(void) -> const callback_type & {
  return *_callback_pool.begin();
}

auto ECS::pop_front(void) -> void { _callback_pool.pop_front(); }

auto ECS::empty(void) const -> bool { return _callback_pool.empty(); }
