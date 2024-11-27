/*
** EPITECH PROJECT, 2024
** piscine
** File description:
** SparseArray.cpp
*/

#pragma once
#include "SparseArray.hpp"

template <typename Component>
SparseArray<Component>::SparseArray()
{
}

template <typename Component>
SparseArray<Component>::SparseArray(const SparseArray &other) // copy constructor
{
    _data = other._data;
}

template <typename Component>
SparseArray<Component>::SparseArray(SparseArray &&other) noexcept // move constructor
{
    _data = std::move(other._data);
}

template <typename Component>
auto SparseArray<Component>::operator=(const SparseArray &other) -> SparseArray & // copy assignment operator
{
    _data = other._data;
    return *this;
}

template <typename Component>
auto SparseArray<Component>::operator=(SparseArray &&other) noexcept -> SparseArray & // move assignment operator
{
    _data = std::move(other._data);
    return *this;
}

template <typename Component>
auto SparseArray<Component>::operator[](size_t idx) -> reference_type
{
    if (idx > _data.size())
        _data.resize(idx+1);
    return _data[idx];
}

template <typename Component>
auto SparseArray<Component>::operator[](size_t idx) const -> const_reference_type
{
    if (idx > _data.size()) {
        static const value_type temp = std::nullopt;
        return temp;
    }
    return _data[idx];
}

template <typename Component>
auto SparseArray<Component>::begin() -> iterator
{
    return _data.begin();
}

template <typename Component>
auto SparseArray<Component>::begin() const -> const_iterator
{
    return _data.begin();
}

template <typename Component>
auto SparseArray<Component>::cbegin() const -> const_iterator
{
    return _data.cbegin();
}

template <typename Component>
auto SparseArray<Component>::end() -> iterator
{
    return _data.end();
}

template <typename Component>
auto SparseArray<Component>::end() const -> const_iterator
{
    return _data.end();
}

template <typename Component>
auto SparseArray<Component>::cend() const -> const_iterator
{
    return _data.cend();
}

template <typename Component>
auto SparseArray<Component>::size() const -> size_type
{
    return _data.size();
}

template <typename Component>
auto SparseArray<Component>::insert_at(size_type pos, const Component &value) -> reference_type
{
    if (pos >= _data.size())
        _data.resize(pos+1);
    _data[pos] = value;
    return _data[pos];
}

template <typename Component>
auto SparseArray<Component>::insert_at(size_type pos, Component &&rvalue) -> reference_type
{
    if (pos >= _data.size())
        _data.resize(pos+1);
    std::move(rvalue);
    return _data.insert_at(pos, rvalue);
}

template <typename Component>
auto SparseArray<Component>::push_back(const Component &value) -> reference_type
{
    return _data.push_back(value);
}

template <typename Component>
template <class ... Params>
auto SparseArray<Component>::emplace_at(size_type pos, Params &&...args) -> reference_type // build the component object in-place.
{
    if (pos >= _data.size())
        _data.resize(pos+1);
    _data[pos].emplace(std::forward<Params>(args)...);
    return _data[pos];
}

template <typename Component>
auto SparseArray<Component>::erase(size_type pos) -> void
{
    if (pos < 0 || pos > _data.size())
        return;
    _data[pos].reset();

}

template <typename Component>
auto SparseArray<Component>::clear(void) -> void
{
    _data.clear();
}
