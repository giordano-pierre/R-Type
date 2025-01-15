/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Singleton.hpp
*/

#pragma once

template <typename T>
class Singleton {
public:
    Singleton() = default;
    ~Singleton() = default;

    static T& getInstance()
    {
        static T instance;
        return instance;
    }
};