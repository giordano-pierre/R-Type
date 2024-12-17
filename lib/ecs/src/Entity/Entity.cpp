/*
** EPITECH PROJECT, 2024
** piscine
** File description:
** Entity.cpp
*/

#include "Entity/Entity.hpp"

Entity::Entity(std::size_t size, bool permanent) {
  _size = size;
  _permanent = permanent;
}

void Entity::setSize(std::size_t size) { _size = size; }

Entity::operator std::size_t() const { return _size; };

void Entity::setState(bool permanent) { _permanent = permanent; }

bool Entity::isPermanent() const { return _permanent; }
