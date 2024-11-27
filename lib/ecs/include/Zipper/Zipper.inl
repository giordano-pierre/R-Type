/*
** EPITECH PROJECT, 2024
** piscine_hub
** File description:
** Zipper.inl
*/

#pragma once


template <class ... Containers>
Zipper<Containers ...>::Zipper(Containers &...cs)
{
    _begin = std::make_tuple(cs.begin()...);
    _end = std::make_tuple(cs.end()...);
    _size = _compute_size(cs...);
    _pred = std::nullopt;
}

template <class ... Containers>
Zipper<Containers ...>::Zipper(pred_type &&pred, Containers &...cs)
{
    _begin = std::make_tuple(cs.begin()...);
    _end = std::make_tuple(cs.end()...);
    _size = _compute_size(cs...);
    _pred = std::move(pred);
}

template <class ... Containers>
auto Zipper<Containers ...>::begin() -> iterator
{
    return iterator(_begin, _size);
}

template <class ... Containers>
auto Zipper<Containers ...>::end() -> iterator
{
    return iterator(_end, _size);
}

// helper function to know the maximum index of our iterators.
template <class ... Containers>
auto Zipper<Containers ...>::_compute_size(Containers &... containers) -> std::size_t
{
    return std::min({ containers.size()... });
}


// helper function to compute an iterator_tuple that will allow us to build our end iterator.
template <class ... Containers>
auto Zipper<Containers ...>::_compute_end(Containers &... containers) -> iterator_tuple
{
    return std::make_tuple(containers.end()...);
}
