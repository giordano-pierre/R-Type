/*
** EPITECH PROJECT, 2024
** piscine_hub
** File description:
** Zipper.hpp
*/

#pragma once
#include <optional>
#include "Iterator.hpp"

template <class ... Containers >
class Zipper {
    public:
        using iterator = ZipperIterator<Containers ...>;
        using iterator_tuple = typename iterator::iterator_tuple;
        using value_type = typename iterator::value_type;
        using pred_type = typename iterator::pred_type;
    public:
        Zipper(Containers &...cs);
        Zipper(pred_type &&pred, Containers &...cs);
        ~Zipper () = default;
        auto begin() -> iterator;
        auto end() -> iterator;

    private:
        // helper function to know the maximum index of our iterators.
        static auto _compute_size(Containers &... containers) -> std::size_t;
        // helper function to compute an iterator_tuple that will allow us to build our end iterator.
        static auto _compute_end(Containers &... containers) -> iterator_tuple;
    private:
        iterator_tuple _begin;
        iterator_tuple _end;
        std::size_t _size;
        std::optional<pred_type > _pred;
};

#include "Zipper.inl"
