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

    public:
        explicit Entity(std::size_t size);
        ~Entity() = default;

        void setSize(std::size_t size);
        operator std::size_t() const;
};
