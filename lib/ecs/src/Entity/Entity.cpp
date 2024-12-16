/*
** EPITECH PROJECT, 2024
** piscine
** File description:
** Entity.cpp
*/

#include "Entity/Entity.hpp"

Entity::Entity(std::size_t size, std::bool permanent)
{
    _size = size;
    _permanent = permanent;
}

void Entity::setSize(std::size_t size)
{
    _size = size;
}

void Entity::setState(std::bool permanent)
{
    _permanent = permanent;
}

Entity::operator std::size_t() const
{
    return _size;
}

bool Entity::isPermanent()const
{
    return _permanent;
}