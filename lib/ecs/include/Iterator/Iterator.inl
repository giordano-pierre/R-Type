/*
** EPITECH PROJECT, 2024
** piscine_hub
** File description:
** Container.cpp
*/

#pragma once
#include "Iterator.hpp"

template <class ... Containers>
ZipperIterator<Containers...>::ZipperIterator(const iterator_tuple &it_tuple, std::size_t max)
{
    _current = it_tuple;
    _max = max;
    _idx = 0;
}

template <class ... Containers>
ZipperIterator<Containers...>::ZipperIterator(const iterator_tuple &it_tuple, std::size_t max, pred_type &&pred)
{
    _current = it_tuple;
    _max = max;
    _pred = pred;
    _idx = 0;
}

template <class ... Containers>
ZipperIterator<Containers...>::ZipperIterator(const ZipperIterator &z)
{
    this = z;
}

template <class ... Containers>
auto ZipperIterator<Containers...>::operator++() -> ZipperIterator &
{
    incr_all(_seq);
    return *this;
}

template <class ... Containers>
auto ZipperIterator<Containers...>::operator++(int) -> ZipperIterator
{
    ZipperIterator tmp = *this;
    this++;
    return tmp;
}

template <class ... Containers>
auto ZipperIterator<Containers...>::operator*() -> value_type
{
    return to_value(_seq);
}

template <class ... Containers>
auto ZipperIterator<Containers...>::operator->() -> value_type
{
    return to_value(_seq);
}

template <class ... Containers>
auto ZipperIterator<Containers...>::operator==(const ZipperIterator <Containers...> &rhs) -> bool
{
    return _current == rhs._current;
}

template <class ... Containers>
auto ZipperIterator<Containers...>::operator!=(const ZipperIterator <Containers...> &rhs) -> bool
{
    return _current != rhs._current;
}

template <class ... Containers>
template <std::size_t ... Is>
auto ZipperIterator<Containers...>::incr_all(std::index_sequence<Is...>) -> void
{
    (std::get<Is>(_current)++, ...);
    _idx++;
    while (_idx < _max && (!all_set(_seq) || (_pred && !(*_pred)(**this)))) {
        (++std::get<Is>(_current)++, ...);
        _idx++;
    }
}

template <class ... Containers>
template <std::size_t ... Is>
auto ZipperIterator<Containers...>::all_set(std::index_sequence<Is...>) -> bool
{
    return (... && *std::get<Is>(_current));
}

template <class ... Containers>
template <std::size_t ... Is>
auto ZipperIterator<Containers...>::to_value(std::index_sequence<Is...>) -> value_type
{
    return std::tuple_cat(std::make_tuple(_idx), std::tie(std::get<Is>(_current)->value()...));
}
