/*
** EPITECH PROJECT, 2024
** piscine
** File description:
** SparseArray.hpp
*/

#pragma once
#include <cstddef>
#include <vector>
#include <optional>

template <typename Component>
class SparseArray {
    public :
        using value_type = std::optional<Component>;
        using reference_type = value_type &;
        using const_reference_type = const value_type &;
        using container_t = std::vector<value_type>;
        using size_type = typename container_t::size_type;
        using iterator = typename container_t::iterator;
        using const_iterator = typename container_t::const_iterator;

        SparseArray();
        SparseArray(const SparseArray &other);
        SparseArray(SparseArray &&other) noexcept;
        ~SparseArray() = default;

        auto operator=(const SparseArray &other) -> SparseArray &;
        auto operator=(SparseArray &&other) noexcept -> SparseArray &;
        auto operator[](size_t idx) -> reference_type;
        auto operator[](size_t idx) const -> const_reference_type;
        auto begin() -> iterator;
        auto begin() const -> const_iterator;
        auto cbegin() const -> const_iterator;
        auto end() -> iterator;
        auto end() const -> const_iterator;
        auto cend() const -> const_iterator;
        auto size() const -> size_type;
        auto insert_at(size_type pos, const Component &value) -> reference_type;
        auto insert_at(size_type pos, Component &&rvalue) -> reference_type;
        auto push_back(const Component &value) -> reference_type;
        template <class ... Params>
        auto emplace_at(size_type pos, Params &&...args) -> reference_type;
        auto erase(size_type pos) -> void;
        auto clear(void) -> void;

    private :
        container_t _data;
};

#include "SparseArray.inl"