/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ReceiveEvent.hpp
*/

#pragma once

#include "NetworkActions.hpp"
#include <nlohmann/json.hpp>
#include <string>

struct ReceiveEvent {
    // ReceiveEvent(NetworkActions action, const nlohmann::json &payload, const
    // std::string &sender_uuid=""):
    //     action(action), payload(payload), sender_uuid(sender_uuid) {};

    const NetworkActions action;
    const nlohmann::json payload;
    const std::string sender_uuid = "";
};
