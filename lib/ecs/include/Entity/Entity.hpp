/*
** EPITECH PROJECT, 2024
** piscine
** File description:
** Entity.hpp
*/

#pragma once
#include <cstddef>

class Entity
{
    private:
        std::size_t _size;
        std::bool _permanent;

    public:
        explicit Entity(std::size_t size, std::bool permanent = false);
        ~Entity() = default;

        void setSize(std::size_t size);
        void setState(std::bool permanent);
        operator std::size_t() const;
        bool isPermanent() const;
};
