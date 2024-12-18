/*
** EPITECH PROJECT, 2024
** piscine
** File description:
** ECS.inl
*/

#pragma once
#include "ECS.hpp"

template <class Component>
auto ECS::register_component() -> SparseArray<Component> &
{
    auto type = std::type_index(typeid(Component));
    auto lambda = [this](const Entity &ent) {
        remove_component<Component>(ent);
    };

    _components_arrays[type] = SparseArray<Component> ();
    _freset_entity_components.push_back(lambda);
    return std::any_cast<SparseArray<Component> &>(_components_arrays[type]);
}

template <class Component>
auto ECS::get_components() -> SparseArray<Component> &
{
    auto type = std::type_index(typeid(Component));

    return std::any_cast<SparseArray<Component> &>(_components_arrays.at(type));
}

template <class Component>
auto ECS::get_components() const -> const SparseArray<Component> &
{
    auto type = std::type_index(typeid(Component));

    return std::any_cast<const SparseArray<Component> &>(_components_arrays.at(type));
}

inline auto ECS::spawn_entity() -> Entity
{
    if (_dead_entities.empty())
        return Entity(_nb_entities++);
    Entity res = *_dead_entities.begin();
    _dead_entities.pop_front();
    return res;
}

inline auto ECS::entity_from_index(std::size_t idx) -> Entity
{
    return Entity(idx);
}

inline auto ECS::kill_entity(const Entity &entity) -> void
{
    for (long unsigned int i = 0; i < _freset_entity_components.size(); i++) {
        _freset_entity_components[i](entity);
    }
    _dead_entities.push_back(entity);
}

template <typename Component>
auto ECS::add_component(Entity const &to, Component &&c) ->
    typename SparseArray<Component>::reference_type
{
    SparseArray<Component> &component_array = get_components<Component>();

    return component_array.insert_at(to, c);
}

template <typename Component, typename ... Params>
auto ECS::emplace_component(Entity const &to, Params &&...p) ->
    typename SparseArray<Component>::reference_type
{
    SparseArray<Component> &component_array = get_components<Component>();

    return component_array.emplace_at(to, p...);
}

template <typename Component>
auto ECS::remove_component(Entity const &from) -> void
{
    SparseArray<Component> &component_array = get_components<Component>();

    component_array.erase(from);
}

template <class Event> auto ECS::register_event() -> void
{
    auto event = std::type_index(typeid(Event));

    _events[event] = systems_type<Event>();
}

template <class Event> auto ECS::get_events() -> systems_type<Event> &
{
    auto event = std::type_index(typeid(Event));

    return std::any_cast<systems_type<Event> &>(_events.at(event));
}

template <class Event>
auto ECS::get_events() const -> const systems_type<Event> &
{
    auto event = std::type_index(typeid(Event));

    return std::any_cast<const systems_type<Event> &>(_events.at(event));
}

template <class Event, class ... Components, typename System>
auto ECS::subscribe(System &&system, bool permanent) -> void
{
    auto lambda = [this, sys = std::move(system)](ECS &ecs, const Event &ev) {
        sys(ecs, ev, get_components<Components>()...);
    };

    systems_type<Event> &event_array = get_events<Event>();

    event_array.push_back({lambda, permanent});
}

template <class Event, class ... Components, typename System>
auto ECS::subscribe(System &system, bool permanent) -> void
{
    auto lambda = [this, &system](ECS &ecs, const Event &ev) {
        system(ecs, ev, get_components<Components>()...);
    };

    systems_type<Event> &event_array = get_events<Event>();

    event_array.push_back({lambda, permanent});
}

template <class Event, class ... Components, typename System>
auto ECS::subscribe(const System &system, bool permanent) -> void
{
    auto lambda = [this, &system](ECS &ecs, const Event &ev) {
        system(ecs, ev, get_components<Components>()...);
    };

    systems_type<Event> &event_array = get_events<Event>();

    event_array.push_back({lambda, permanent});
}

template <class Event>
auto ECS::clean() -> void
{
    auto event = std::type_index(typeid(Event));
    systems_type<Event> &event_array = get_events<Event>();

    event_array.erase(
        std::remove_if(event_array.begin(), event_array.end(), [](const auto &system) {
            return !system.permanent;
        }),
        event_array.end()
    );
}

template <class Event> auto ECS::post(const Event &event) -> void
{
    auto lambda = [this, event]() {
        systems_type<Event> &event_array = get_events<Event>();
        for (long unsigned int i = 0; i < event_array.size(); i++)
            event_array[i].lambda(*this, std::move(event));
    };

    _callback_pool.push_back(lambda);
}
