/*
** EPITECH PROJECT, 2024
** piscine_hub
** File description:
** Container.hpp
*/

#pragma once
#include <cstddef>
#include <utility>

template <class... Containers> class ZipperIterator {
  template <class Container>
  using iterator_t = decltype(std::begin(
      std::declval<Container &>())); // type of Container::begin() return value

  template <class Container>
  using it_reference_t = typename iterator_t<Container>::reference;

public:
  using value_type = std::tuple<
      std::size_t,
      decltype(std::declval<it_reference_t<Containers>>().value()) &...>;
  // std::tuple of references to components

  using reference = value_type;
  using iterator_category = std::input_iterator_tag;
  using iterator_tuple = std::tuple<iterator_t<Containers>...>;
  using pred_type = std::function<bool(const value_type &)>;

public:
  ZipperIterator(const iterator_tuple &it_tuple, std::size_t max);
  ZipperIterator(const iterator_tuple &it_tuple, std::size_t max,
                 pred_type &&pred);
  ZipperIterator(const ZipperIterator &z);
  ~ZipperIterator() = default;

  auto operator++() -> ZipperIterator &;
  auto operator++(int) -> ZipperIterator;
  auto operator*() -> value_type;
  auto operator->() -> value_type;
  auto operator==(const ZipperIterator<Containers...> &rhs) -> bool;
  auto operator!=(const ZipperIterator<Containers...> &rhs) -> bool;

private:
  // Increment every iterator at the same time. It also skips to the next value
  // if
  //      one of the pointed to std:: optional does not contains a value or
  //      according to the predicate function if specified.
  template <std::size_t... Is>
  auto incr_all(std::index_sequence<Is...>) -> void;

  // check if every std:: optional are set.
  template <std::size_t... Is> auto all_set(std::index_sequence<Is...>) -> bool;
  // return a tuple of reference to components.
  template <std::size_t... Is>
  auto to_value(std::index_sequence<Is...>) -> value_type;

private:
  iterator_tuple _current;
  std::size_t _max; // compare this value to _idx to prevent infinite loop.
  std::size_t _idx;
  std::optional<pred_type> _pred;
  static constexpr std::index_sequence_for<Containers...> _seq{};
};

#include "Iterator.inl"