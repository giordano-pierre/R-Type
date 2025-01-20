/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CreationEvent
*/

#pragma once

#include "clientTools.hpp"
#include "events/ReceiveEvent.hpp"
#include <optional>

namespace rtype::client {
struct CreationEvent {
    SceneType _type;
    std::optional<ReceiveEvent> _param;
};
} // namespace rtype::client
